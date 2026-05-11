#include "RecordingPluginSubsystem.h"
#include "Async/Async.h"
#include "SubmixAudioCapture.h"
#include "WMFEncoder.h"
#include "FrameGrabber.h"

#include "AudioThread.h"
#include "AudioDevice.h"
#include "Containers/Ticker.h"
#include "Engine/GameViewportClient.h"
#include "Engine/GameEngine.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformMemory.h"
#include "Misc/App.h"
#include "RenderCommandFence.h"
#include "RHI.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "UnrealClient.h"

#include "ID3D11DynamicRHI.h"

DEFINE_LOG_CATEGORY_STATIC(LogRecordingPlugin, Log, All);

void FWMFEncoderDeleter::operator()(FWMFEncoder* Ptr) const
{
	delete Ptr;
}

void FRecordingFrameGrabberDeleter::operator()(FRecordingFrameGrabber* Ptr) const
{
	delete Ptr;
}

void FSubmixAudioCaptureDeleter::operator()(FSubmixAudioCapture* Ptr) const
{
	delete Ptr;
}

struct FAsyncRecordingStopContext
{
	TUniquePtr<FWMFEncoder, FWMFEncoderDeleter> Encoder;
	TUniquePtr<FRecordingFrameGrabber, FRecordingFrameGrabberDeleter> Grabber;
	TUniquePtr<FSubmixAudioCapture, FSubmixAudioCaptureDeleter> AudioCapture;
	FRenderCommandFence RenderFence;
	FAudioCommandFence AudioFence;
	FString FinishedPath;
	int32 TotalFrames = 0;
	bool bWaitingForRenderFence = false;
	bool bWaitingForAudioFence = false;
	bool bFinalizeStarted = false;
	TFuture<void> FinalizeTask;
	TAtomic<bool> bFinalizeComplete { false };
};

void FAsyncRecordingStopContextDeleter::operator()(FAsyncRecordingStopContext* Ptr) const
{
	delete Ptr;
}

// ────────────────────────────────────────────────────────────────────────────
// 构造 / 析构（TUniquePtr 需要完整类型可见）
// ────────────────────────────────────────────────────────────────────────────

URecordingPluginSubsystem::URecordingPluginSubsystem() = default;
URecordingPluginSubsystem::~URecordingPluginSubsystem()
{
	StopPendingStopTicker();
	StopPerformanceMonitorTicker();
	StopRecordingPerformanceTicker();
}

// ────────────────────────────────────────────────────────────────────────────
// Subsystem 生命周期
// ────────────────────────────────────────────────────────────────────────────

void URecordingPluginSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogRecordingPlugin, Log, TEXT("RecordingPluginSubsystem initialized."));
}

void URecordingPluginSubsystem::Deinitialize()
{
	ClosePerformanceMonitorWindow();

	if (bRecording)
	{
		UE_LOG(LogRecordingPlugin, Warning,
		       TEXT("Subsystem deinitializing while recording, auto-stopping."));
		StopRecording();
	}

	if (PendingStopContext)
	{
		ForceCompletePendingStop(true);
	}

	Super::Deinitialize();
}

// ────────────────────────────────────────────────────────────────────────────
// 开始录制
// ────────────────────────────────────────────────────────────────────────────

bool URecordingPluginSubsystem::StartRecording(const FString& OutputPath,
                                                int32 FPS, int32 BitrateMbps)
{
	const double StartCallSeconds = FPlatformTime::Seconds();

	if (bRecording)
	{
		BroadcastError(TEXT("Already recording. Call StopRecording first."));
		return false;
	}
	if (PendingStopContext)
	{
		BroadcastError(TEXT("Previous recording is still finalizing. Wait for OnRecordingFinished before starting again."));
		return false;
	}

	// ── 参数校验 ─────────────────────────────────────────────────────────
	FPS = FMath::Clamp(FPS, 1, 120);
	BitrateMbps = FMath::Clamp(BitrateMbps, 1, 100);

	// ── 检测 RHI（本分支仅支持 D3D11）───────────────────────────────────
	void* NativeDevice = nullptr;
	if (!DetectRHI(NativeDevice))
	{
		BroadcastError(TEXT("Failed to detect D3D11 RHI or get native device. Launch the project with -d3d11."));
		return false;
	}

	// ── 获取视口分辨率 ──────────────────────────────────────────────────
	int32 W = 0, H = 0;
	if (!GetViewportResolution(W, H))
	{
		BroadcastError(TEXT("Failed to get game viewport resolution."));
		return false;
	}

	// 编码器要求宽高为偶数
	W = W & ~1;
	H = H & ~1;
	if (W <= 0 || H <= 0)
	{
		BroadcastError(FString::Printf(TEXT("Invalid resolution: %dx%d"), W, H));
		return false;
	}

	BeginRecordingPerformanceStats();

	// ── 自动创建输出目录 ────────────────────────────────────────────────
	const FString Directory = FPaths::GetPath(OutputPath);
	if (!Directory.IsEmpty())
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (!PlatformFile.DirectoryExists(*Directory))
		{
			PlatformFile.CreateDirectoryTree(*Directory);
		}
	}

	// ── 初始化 WMF 编码器 ───────────────────────────────────────────────
	FAudioDeviceHandle AudioDeviceHandle;
	int32 AudioSampleRate = 0;
	if (UWorld* World = GetWorld())
	{
		AudioDeviceHandle = World->GetAudioDevice();
	}
	if (!AudioDeviceHandle.IsValid() && GEngine)
	{
		AudioDeviceHandle = GEngine->GetMainAudioDevice();
	}
	if (AudioDeviceHandle.IsValid())
	{
		AudioSampleRate = FMath::RoundToInt(AudioDeviceHandle->GetSampleRate());
		if (AudioSampleRate != 44100 && AudioSampleRate != 48000)
		{
			UE_LOG(LogRecordingPlugin, Warning,
			       TEXT("UE audio capture disabled because audio device sample rate %dHz is unsupported by WMF AAC."),
			       AudioSampleRate);
			AudioDeviceHandle.Reset();
			AudioSampleRate = 0;
		}
	}
	else
	{
		UE_LOG(LogRecordingPlugin, Warning, TEXT("No valid UE audio device found. Recording will continue without audio."));
	}

	Encoder = TUniquePtr<FWMFEncoder, FWMFEncoderDeleter>(new FWMFEncoder());
	const double EncoderInitStartSeconds = FPlatformTime::Seconds();
	if (!Encoder->Initialize(OutputPath, W, H, FPS, BitrateMbps, NativeDevice,
	                         AudioSampleRate, AudioSampleRate > 0 ? 2 : 0))
	{
		BroadcastError(TEXT("GPU encoder initialization failed. Check that D3D11 is active and the HardwareEncoders plugin is enabled."));
		Encoder.Reset();
		StopRecordingPerformanceTicker();
		return false;
	}
	RecordingPerformanceStats.EncoderInitCostMs = static_cast<float>(
		(FPlatformTime::Seconds() - EncoderInitStartSeconds) * 1000.0);

	// ── 初始化帧捕获器 ─────────────────────────────────────────────────
	Grabber = TUniquePtr<FRecordingFrameGrabber, FRecordingFrameGrabberDeleter>(new FRecordingFrameGrabber());
	FSceneViewport* TargetViewport = GEngine && GEngine->GameViewport ? GEngine->GameViewport->GetGameViewport() : nullptr;
	SWindow* TargetWindow = GEngine && GEngine->GameViewport ? GEngine->GameViewport->GetWindow().Get() : nullptr;
	const double FrameGrabberInitStartSeconds = FPlatformTime::Seconds();
	if (!Grabber->Initialize(W, H, FPS, TargetViewport, TargetWindow, Encoder.Get()))
	{
		BroadcastError(TEXT("FrameGrabber initialization failed."));
		Encoder->Finalize();
		Encoder.Reset();
		Grabber.Reset();
		StopRecordingPerformanceTicker();
		return false;
	}
	RecordingPerformanceStats.FrameGrabberInitCostMs = static_cast<float>(
		(FPlatformTime::Seconds() - FrameGrabberInitStartSeconds) * 1000.0);

	if (AudioDeviceHandle.IsValid() && Encoder->HasAudioStream())
	{
		AudioCapture = TUniquePtr<FSubmixAudioCapture, FSubmixAudioCaptureDeleter>(new FSubmixAudioCapture());
		const double AudioCaptureInitStartSeconds = FPlatformTime::Seconds();
		if (!AudioCapture->Initialize(AudioDeviceHandle, Encoder.Get()))
		{
			UE_LOG(LogRecordingPlugin, Warning,
			       TEXT("UE audio capture initialization failed. Recording will continue without audio samples."));
			AudioCapture.Reset();
		}
		RecordingPerformanceStats.AudioCaptureInitCostMs = static_cast<float>(
			(FPlatformTime::Seconds() - AudioCaptureInitStartSeconds) * 1000.0);
	}

	// ── 监听视口大小变化 ────────────────────────────────────────────────
	ViewportResizedHandle = FViewport::ViewportResizedEvent.AddUObject(
		this, &URecordingPluginSubsystem::OnViewportResized);

	// ── 记录状态 ────────────────────────────────────────────────────────
	bRecording       = true;
	TargetFPS        = FPS;
	Resolution       = FIntPoint(W, H);
	CurrentOutputPath = OutputPath;
	RecordingPerformanceStats.StartRecordingCostMs = static_cast<float>(
		(FPlatformTime::Seconds() - StartCallSeconds) * 1000.0);

	UE_LOG(LogRecordingPlugin, Log,
	       TEXT("Recording started: %s (%dx%d @%dfps %dMbps D3D11 GPU%s)"),
	       *OutputPath, W, H, FPS, BitrateMbps,
	       AudioCapture ? TEXT(" + UEAudio") : TEXT(""));
	return true;
}

// ────────────────────────────────────────────────────────────────────────────
// 停止录制
// ────────────────────────────────────────────────────────────────────────────

void URecordingPluginSubsystem::StopRecording()
{
	if (PendingStopContext)
	{
		UE_LOG(LogRecordingPlugin, Verbose, TEXT("StopRecording ignored because finalize is already in progress."));
		return;
	}

	if (!bRecording)
	{
		return;
	}

	bRecording = false;
	EndRecordingPerformanceSampling();
	RecordingStopRequestSeconds = FPlatformTime::Seconds();

	// 取消视口变化监听
	if (ViewportResizedHandle.IsValid())
	{
		FViewport::ViewportResizedEvent.Remove(ViewportResizedHandle);
		ViewportResizedHandle.Reset();
	}

	PendingStopContext = TUniquePtr<FAsyncRecordingStopContext, FAsyncRecordingStopContextDeleter>(
		new FAsyncRecordingStopContext());
	PendingStopContext->FinishedPath = CurrentOutputPath;
	PendingStopContext->Encoder = MoveTemp(Encoder);
	PendingStopContext->Grabber = MoveTemp(Grabber);
	PendingStopContext->AudioCapture = MoveTemp(AudioCapture);

	if (PendingStopContext->AudioCapture)
	{
		PendingStopAudioFenceStartSeconds = FPlatformTime::Seconds();
		PendingStopContext->AudioCapture->BeginShutdown();
		PendingStopContext->AudioFence.BeginFence();
		PendingStopContext->bWaitingForAudioFence = true;
	}
	else
	{
		PendingStopAudioFenceStartSeconds = 0.0;
	}

	if (PendingStopContext->Grabber)
	{
		PendingStopRenderFenceStartSeconds = FPlatformTime::Seconds();
		PendingStopContext->Grabber->BeginShutdown();
		PendingStopContext->RenderFence.BeginFence();
		PendingStopContext->bWaitingForRenderFence = true;
	}
	else
	{
		PendingStopRenderFenceStartSeconds = 0.0;
	}

	UE_LOG(LogRecordingPlugin, Log,
	       TEXT("Recording stop requested asynchronously: %s"), *PendingStopContext->FinishedPath);

	StartPendingStopTicker();
}

// ────────────────────────────────────────────────────────────────────────────
// 查询
// ────────────────────────────────────────────────────────────────────────────

int32 URecordingPluginSubsystem::GetFrameCount() const
{
	if (Grabber)
	{
		return Grabber->GetFrameCount();
	}
	if (PendingStopContext)
	{
		return PendingStopContext->Grabber
			? PendingStopContext->Grabber->GetFrameCount()
			: PendingStopContext->TotalFrames;
	}
	return 0;
}

float URecordingPluginSubsystem::GetRecordedSeconds() const
{
	if (TargetFPS <= 0)
	{
		return 0.0f;
	}
	return static_cast<float>(GetFrameCount()) / static_cast<float>(TargetFPS);
}

// ────────────────────────────────────────────────────────────────────────────
// 性能监控窗口
// ────────────────────────────────────────────────────────────────────────────

bool URecordingPluginSubsystem::OpenPerformanceMonitorWindow()
{
	if (IsPerformanceMonitorWindowOpen())
	{
		return true;
	}

	if (!FSlateApplication::IsInitialized())
	{
		BroadcastError(TEXT("Cannot open performance monitor window because SlateApplication is not initialized."));
		return false;
	}

	PerformanceMonitorRows = SNew(SVerticalBox);

	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.Title(FText::FromString(TEXT("录制性能监控")))
		.ClientSize(FVector2D(820.0f, 640.0f))
		.SupportsMaximize(true)
		.SupportsMinimize(true);

	NewWindow->SetOnWindowClosed(FOnWindowClosed::CreateUObject(
		this, &URecordingPluginSubsystem::OnPerformanceMonitorWindowClosed));

	NewWindow->SetContent(
		SNew(SBorder)
		.Padding(FMargin(12.0f))
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(SCheckBox)
					.IsChecked_Lambda([this]()
					{
						return bPerformanceMonitorShowDescriptions
							? ECheckBoxState::Checked
							: ECheckBoxState::Unchecked;
					})
					.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
					{
						bPerformanceMonitorShowDescriptions = NewState == ECheckBoxState::Checked;
						RefreshPerformanceMonitorWindowRows();
					})
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(6.0f, 0.0f, 0.0f, 0.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("显示说明")))
				]
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					PerformanceMonitorRows.ToSharedRef()
				]
			]
		]);

	PerformanceMonitorWindow = NewWindow;
	RefreshPerformanceMonitorWindowRows();
	FSlateApplication::Get().AddWindow(NewWindow);
	StartPerformanceMonitorTicker();

	UE_LOG(LogRecordingPlugin, Log, TEXT("Performance monitor window opened."));
	return true;
}

void URecordingPluginSubsystem::ClosePerformanceMonitorWindow()
{
	StopPerformanceMonitorTicker();

	TSharedPtr<SWindow> Window = PerformanceMonitorWindow.Pin();
	PerformanceMonitorWindow.Reset();
	PerformanceMonitorRows.Reset();

	if (Window.IsValid() && FSlateApplication::IsInitialized())
	{
		Window->RequestDestroyWindow();
	}
}

void URecordingPluginSubsystem::TogglePerformanceMonitorWindow()
{
	if (IsPerformanceMonitorWindowOpen())
	{
		ClosePerformanceMonitorWindow();
	}
	else
	{
		OpenPerformanceMonitorWindow();
	}
}

bool URecordingPluginSubsystem::IsPerformanceMonitorWindowOpen() const
{
	const TSharedPtr<SWindow> Window = PerformanceMonitorWindow.Pin();
	return Window.IsValid();
}

// ────────────────────────────────────────────────────────────────────────────
// 内部
// ────────────────────────────────────────────────────────────────────────────

bool URecordingPluginSubsystem::DetectRHI(void*& OutNativeDevice) const
{
	if (!GDynamicRHI)
	{
		UE_LOG(LogRecordingPlugin, Error, TEXT("GDynamicRHI is null."));
		return false;
	}

	const FString RHIName = GDynamicRHI->GetName();

	if (RHIName == TEXT("D3D11"))
	{
		if (ID3D11DynamicRHI* RHI11 = GetID3D11DynamicRHI())
		{
			OutNativeDevice = RHI11->RHIGetDevice();
			return OutNativeDevice != nullptr;
		}
	}

	UE_LOG(LogRecordingPlugin, Error,
	       TEXT("Unsupported RHI: %s. This gpu-dx11 branch only supports D3D11."), *RHIName);
	return false;
}

bool URecordingPluginSubsystem::GetViewportResolution(int32& OutWidth, int32& OutHeight) const
{
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		const FIntPoint Size = GEngine->GameViewport->Viewport->GetSizeXY();
		OutWidth  = Size.X;
		OutHeight = Size.Y;
		return OutWidth > 0 && OutHeight > 0;
	}

	return false;
}

void URecordingPluginSubsystem::BroadcastError(const FString& Msg)
{
	UE_LOG(LogRecordingPlugin, Error, TEXT("%s"), *Msg);
	OnRecordingError.Broadcast(Msg);
}

void URecordingPluginSubsystem::OnViewportResized(FViewport* /*Viewport*/, uint32 /*Unused*/)
{
	if (bRecording)
	{
		UE_LOG(LogRecordingPlugin, Warning,
		       TEXT("Viewport resized during recording — auto-stopping to prevent corruption."));
		StopRecording();
	}
}

bool URecordingPluginSubsystem::TickPendingStop(float DeltaTime)
{
	(void)DeltaTime;

	if (!PendingStopContext)
	{
		StopPendingStopTicker();
		return false;
	}

	FAsyncRecordingStopContext& StopContext = *PendingStopContext;
	if (!StopContext.bFinalizeStarted)
	{
		const bool bRenderFenceComplete =
			!StopContext.bWaitingForRenderFence || StopContext.RenderFence.IsFenceComplete();
		const bool bAudioFenceComplete =
			!StopContext.bWaitingForAudioFence || StopContext.AudioFence.IsFenceComplete();

		if (bRenderFenceComplete && StopContext.bWaitingForRenderFence && PendingStopRenderFenceStartSeconds > 0.0)
		{
			RecordingPerformanceStats.RenderFenceWaitMs = static_cast<float>(
				(FPlatformTime::Seconds() - PendingStopRenderFenceStartSeconds) * 1000.0);
			PendingStopRenderFenceStartSeconds = 0.0;
		}
		if (bAudioFenceComplete && StopContext.bWaitingForAudioFence && PendingStopAudioFenceStartSeconds > 0.0)
		{
			RecordingPerformanceStats.AudioFenceWaitMs = static_cast<float>(
				(FPlatformTime::Seconds() - PendingStopAudioFenceStartSeconds) * 1000.0);
			PendingStopAudioFenceStartSeconds = 0.0;
		}

		if (!bRenderFenceComplete || !bAudioFenceComplete)
		{
			return true;
		}

		if (StopContext.Grabber)
		{
			StopContext.TotalFrames = StopContext.Grabber->GetFrameCount();
			StopContext.Grabber->CompleteShutdown();
			StopContext.Grabber.Reset();
		}

		if (StopContext.AudioCapture)
		{
			StopContext.AudioCapture->CompleteShutdown();
			StopContext.AudioCapture.Reset();
		}

		StopContext.bWaitingForRenderFence = false;
		StopContext.bWaitingForAudioFence = false;
		StopContext.bFinalizeStarted = true;
		PendingStopFinalizeStartSeconds = FPlatformTime::Seconds();

		if (StopContext.Encoder)
		{
			FAsyncRecordingStopContext* const ContextPtr = PendingStopContext.Get();
			TUniquePtr<FWMFEncoder, FWMFEncoderDeleter> EncoderToFinalize = MoveTemp(StopContext.Encoder);
			StopContext.FinalizeTask = Async(EAsyncExecution::Thread, [ContextPtr, Encoder = MoveTemp(EncoderToFinalize)]() mutable
			{
				if (Encoder)
				{
					Encoder->Finalize();
					Encoder.Reset();
				}
				ContextPtr->bFinalizeComplete.Store(true);
			});
		}
		else
		{
			StopContext.bFinalizeComplete.Store(true);
		}

		return true;
	}

	if (!StopContext.bFinalizeComplete.Load())
	{
		return true;
	}

	if (StopContext.FinalizeTask.IsValid())
	{
		StopContext.FinalizeTask.Wait();
	}

	if (PendingStopFinalizeStartSeconds > 0.0)
	{
		RecordingPerformanceStats.FinalizeCostMs = static_cast<float>(
			(FPlatformTime::Seconds() - PendingStopFinalizeStartSeconds) * 1000.0);
		PendingStopFinalizeStartSeconds = 0.0;
	}

	if (RecordingStopRequestSeconds > 0.0)
	{
		RecordingPerformanceStats.StopTotalCostMs = static_cast<float>(
			(FPlatformTime::Seconds() - RecordingStopRequestSeconds) * 1000.0);
		RecordingStopRequestSeconds = 0.0;
	}
	UpdateRecordingMemoryStats();

	const FString FinishedPath = StopContext.FinishedPath;
	const int32 TotalFrames = StopContext.TotalFrames;

	PendingStopContext.Reset();
	StopPendingStopTicker();

	UE_LOG(LogRecordingPlugin, Log,
	       TEXT("Recording stopped: %s (Total frames: %d)"), *FinishedPath, TotalFrames);

	OnRecordingFinished.Broadcast(FinishedPath);
	return false;
}

void URecordingPluginSubsystem::StartPendingStopTicker()
{
	if (!PendingStopTickerHandle.IsValid())
	{
		PendingStopTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &URecordingPluginSubsystem::TickPendingStop), 0.0f);
	}
}

void URecordingPluginSubsystem::StopPendingStopTicker()
{
	if (PendingStopTickerHandle.IsValid())
	{
		FTSTicker::RemoveTicker(PendingStopTickerHandle);
		PendingStopTickerHandle.Reset();
	}
}

void URecordingPluginSubsystem::ForceCompletePendingStop(bool bBroadcastFinished)
{
	StopPendingStopTicker();

	if (!PendingStopContext)
	{
		return;
	}

	FAsyncRecordingStopContext& StopContext = *PendingStopContext;

	if (StopContext.bWaitingForRenderFence)
	{
		const double WaitStartSeconds = FPlatformTime::Seconds();
		StopContext.RenderFence.Wait();
		RecordingPerformanceStats.RenderFenceWaitMs += static_cast<float>(
			(FPlatformTime::Seconds() - WaitStartSeconds) * 1000.0);
		StopContext.bWaitingForRenderFence = false;
	}
	if (StopContext.Grabber)
	{
		StopContext.TotalFrames = StopContext.Grabber->GetFrameCount();
		StopContext.Grabber->CompleteShutdown();
		StopContext.Grabber.Reset();
	}

	if (StopContext.bWaitingForAudioFence)
	{
		const double WaitStartSeconds = FPlatformTime::Seconds();
		StopContext.AudioFence.Wait();
		RecordingPerformanceStats.AudioFenceWaitMs += static_cast<float>(
			(FPlatformTime::Seconds() - WaitStartSeconds) * 1000.0);
		StopContext.bWaitingForAudioFence = false;
	}
	if (StopContext.AudioCapture)
	{
		StopContext.AudioCapture->CompleteShutdown();
		StopContext.AudioCapture.Reset();
	}

	if (StopContext.bFinalizeStarted)
	{
		if (StopContext.FinalizeTask.IsValid())
		{
			const double FinalizeWaitStartSeconds = FPlatformTime::Seconds();
			StopContext.FinalizeTask.Wait();
			RecordingPerformanceStats.FinalizeCostMs += static_cast<float>(
				(FPlatformTime::Seconds() - FinalizeWaitStartSeconds) * 1000.0);
		}
	}
	else if (StopContext.Encoder)
	{
		const double FinalizeStartSeconds = FPlatformTime::Seconds();
		StopContext.Encoder->Finalize();
		RecordingPerformanceStats.FinalizeCostMs += static_cast<float>(
			(FPlatformTime::Seconds() - FinalizeStartSeconds) * 1000.0);
		StopContext.Encoder.Reset();
	}

	if (RecordingStopRequestSeconds > 0.0)
	{
		RecordingPerformanceStats.StopTotalCostMs = static_cast<float>(
			(FPlatformTime::Seconds() - RecordingStopRequestSeconds) * 1000.0);
		RecordingStopRequestSeconds = 0.0;
	}
	UpdateRecordingMemoryStats();

	const FString FinishedPath = StopContext.FinishedPath;
	const int32 TotalFrames = StopContext.TotalFrames;

	PendingStopContext.Reset();

	UE_LOG(LogRecordingPlugin, Log,
	       TEXT("Recording stopped: %s (Total frames: %d)"), *FinishedPath, TotalFrames);

	if (bBroadcastFinished)
	{
		OnRecordingFinished.Broadcast(FinishedPath);
	}
}

bool URecordingPluginSubsystem::TickPerformanceMonitorWindow(float DeltaTime)
{
	(void)DeltaTime;

	if (!IsPerformanceMonitorWindowOpen() || !PerformanceMonitorRows.IsValid())
	{
		StopPerformanceMonitorTicker();
		return false;
	}

	RefreshPerformanceMonitorWindowRows();
	return true;
}

void URecordingPluginSubsystem::StartPerformanceMonitorTicker()
{
	if (!PerformanceMonitorTickerHandle.IsValid())
	{
		PerformanceMonitorTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &URecordingPluginSubsystem::TickPerformanceMonitorWindow), 0.25f);
	}
}

void URecordingPluginSubsystem::StopPerformanceMonitorTicker()
{
	if (PerformanceMonitorTickerHandle.IsValid())
	{
		FTSTicker::RemoveTicker(PerformanceMonitorTickerHandle);
		PerformanceMonitorTickerHandle.Reset();
	}
}

void URecordingPluginSubsystem::AddPerformanceMonitorSection(const FString& Title)
{
	if (!PerformanceMonitorRows.IsValid())
	{
		return;
	}

	PerformanceMonitorRows->AddSlot()
	.AutoHeight()
	.Padding(0.0f, PerformanceMonitorRowIndex > 0 ? 12.0f : 0.0f, 0.0f, 6.0f)
	[
		SNew(STextBlock)
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
		.Text(FText::FromString(Title))
	];

	PerformanceMonitorRows->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 0.0f, 0.0f, 4.0f)
	[
		SNew(SSeparator)
	];
}

void URecordingPluginSubsystem::AddPerformanceMonitorRow(const FString& Name, const FString& Value, const FString& Description)
{
	if (!PerformanceMonitorRows.IsValid())
	{
		return;
	}

	const bool bIsEvenRow = PerformanceMonitorRowIndex % 2 == 0;
	const FLinearColor RowColor = bIsEvenRow
		? FLinearColor(0.08f, 0.08f, 0.08f, 0.70f)
		: FLinearColor(0.14f, 0.14f, 0.14f, 0.70f);
	++PerformanceMonitorRowIndex;

	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(0.28f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
			.Text(FText::FromString(Name))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(0.22f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(FCoreStyle::GetDefaultFontStyle("Mono", 10))
			.Text(FText::FromString(Value))
		];

	if (bPerformanceMonitorShowDescriptions)
	{
		Row->AddSlot()
		.FillWidth(0.50f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
			.ColorAndOpacity(FSlateColor(FLinearColor(0.72f, 0.72f, 0.72f, 1.0f)))
			.AutoWrapText(true)
			.Text(FText::FromString(Description))
		];
	}

	PerformanceMonitorRows->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 1.0f, 0.0f, 1.0f)
	[
		SNew(SBorder)
		.Padding(FMargin(8.0f, 5.0f))
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		.BorderBackgroundColor(RowColor)
		[
			Row
		]
	];
}

void URecordingPluginSubsystem::RefreshPerformanceMonitorWindowRows()
{
	if (!PerformanceMonitorRows.IsValid())
	{
		return;
	}

	PerformanceMonitorRows->ClearChildren();
	PerformanceMonitorRowIndex = 0;

	const double FrameDeltaSeconds = FApp::GetDeltaTime();
	const double AverageFPS = FrameDeltaSeconds > 0.0 ? 1.0 / FrameDeltaSeconds : 0.0;
	const double AverageDeltaMs = FrameDeltaSeconds * 1000.0;
	const FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
	const double UsedPhysicalMB = static_cast<double>(MemoryStats.UsedPhysical) / 1024.0 / 1024.0;
	const double PeakUsedPhysicalMB = static_cast<double>(MemoryStats.PeakUsedPhysical) / 1024.0 / 1024.0;
	const FString RHIName = GDynamicRHI ? GDynamicRHI->GetName() : TEXT("None");
	const FString ResolutionText = Resolution != FIntPoint::ZeroValue
		? FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y)
		: TEXT("None");
	const FString ViewportText = [&]() -> FString
	{
		int32 W = 0;
		int32 H = 0;
		return GetViewportResolution(W, H)
			? FString::Printf(TEXT("%dx%d"), W, H)
			: TEXT("Unavailable");
	}();

	AddPerformanceMonitorSection(TEXT("性能概览（当前帧）"));
	AddPerformanceMonitorRow(TEXT("当前 FPS"), FString::Printf(TEXT("%.1f"), AverageFPS), TEXT("由当前帧 DeltaTime 换算。"));
	AddPerformanceMonitorRow(TEXT("当前帧耗时"), FString::Printf(TEXT("%.2f ms"), AverageDeltaMs), TEXT("当前游戏帧 DeltaTime。"));
	AddPerformanceMonitorRow(TEXT("当前物理内存"), FString::Printf(TEXT("%.1f MB"), UsedPhysicalMB), TEXT("进程当前使用的物理内存。"));
	AddPerformanceMonitorRow(TEXT("峰值物理内存"), FString::Printf(TEXT("%.1f MB"), PeakUsedPhysicalMB), TEXT("本进程历史峰值物理内存。"));
	AddPerformanceMonitorRow(TEXT("渲染接口 RHI"), RHIName, TEXT("录制模块仅支持 D3D11。"));
	AddPerformanceMonitorRow(TEXT("当前视口"), ViewportText, TEXT("游戏视口实时分辨率。"));

	AddPerformanceMonitorSection(TEXT("录制状态"));
	AddPerformanceMonitorRow(TEXT("状态"), bRecording ? TEXT("Recording") : TEXT("Idle"), TEXT("Recording=正在录制，Idle=空闲。"));
	AddPerformanceMonitorRow(TEXT("正在收尾"), PendingStopContext ? TEXT("Yes") : TEXT("No"), TEXT("Yes 表示 MP4 正在后台 finalize。"));
	AddPerformanceMonitorRow(TEXT("目标 FPS"), LexToString(TargetFPS), TEXT("写入视频时使用的目标帧率。"));
	AddPerformanceMonitorRow(TEXT("录制分辨率"), ResolutionText, TEXT("开始录制时锁定的偶数分辨率。"));
	AddPerformanceMonitorRow(TEXT("已提交帧数"), LexToString(GetFrameCount()), TEXT("已提交给编码器的视频帧数。"));
	AddPerformanceMonitorRow(TEXT("已录制时长"), FString::Printf(TEXT("%.2f 秒"), GetRecordedSeconds()), TEXT("按已提交帧数 / 目标 FPS 估算。"));
	AddPerformanceMonitorRow(TEXT("输出路径"), CurrentOutputPath.IsEmpty() ? TEXT("None") : CurrentOutputPath, TEXT("当前录制输出 MP4 的完整路径。"));

	AddPerformanceMonitorSection(TEXT("录制性能统计"));
	AddPerformanceMonitorRow(TEXT("采样数"), LexToString(RecordingPerformanceStats.SampleCount), TEXT("录制期间采集到的游戏帧样本数。"));
	AddPerformanceMonitorRow(TEXT("平均 FPS"), FString::Printf(TEXT("%.1f"), RecordingPerformanceStats.AverageFPS), TEXT("录制期间平均帧率。"));
	AddPerformanceMonitorRow(TEXT("1% Low FPS"), FString::Printf(TEXT("%.1f"), RecordingPerformanceStats.OnePercentLowFPS), TEXT("最慢 1% 帧的平均 FPS，用于观察卡顿。"));
	AddPerformanceMonitorRow(TEXT("0.1% Low FPS"), FString::Printf(TEXT("%.1f"), RecordingPerformanceStats.ZeroPointOnePercentLowFPS), TEXT("最慢 0.1% 帧的平均 FPS，用于观察尖峰卡顿。"));
	AddPerformanceMonitorRow(TEXT("平均帧耗时"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.AverageFrameTimeMs), TEXT("录制期间平均游戏帧耗时。"));
	AddPerformanceMonitorRow(TEXT("最差帧耗时"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.WorstFrameTimeMs), TEXT("录制期间单帧最高耗时。"));
	AddPerformanceMonitorRow(TEXT("开始录制总耗时"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.StartRecordingCostMs), TEXT("StartRecording 调用整体耗时。"));
	AddPerformanceMonitorRow(TEXT("编码器初始化"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.EncoderInitCostMs), TEXT("Media Foundation / GPU H.264 编码器初始化耗时。"));
	AddPerformanceMonitorRow(TEXT("画面捕获初始化"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.FrameGrabberInitCostMs), TEXT("BackBuffer 捕获器初始化耗时。"));
	AddPerformanceMonitorRow(TEXT("音频捕获初始化"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.AudioCaptureInitCostMs), TEXT("主 Submix 音频捕获初始化耗时。"));
	AddPerformanceMonitorRow(TEXT("渲染 Fence 等待"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.RenderFenceWaitMs), TEXT("停止录制时等待渲染线程完成的耗时。"));
	AddPerformanceMonitorRow(TEXT("音频 Fence 等待"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.AudioFenceWaitMs), TEXT("停止录制时等待音频线程完成的耗时。"));
	AddPerformanceMonitorRow(TEXT("MP4 收尾耗时"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.FinalizeCostMs), TEXT("SinkWriter Finalize 写入尾部索引的耗时。"));
	AddPerformanceMonitorRow(TEXT("停止录制总耗时"), FString::Printf(TEXT("%.2f ms"), RecordingPerformanceStats.StopTotalCostMs), TEXT("StopRecording 到完成广播的总耗时。"));
	AddPerformanceMonitorRow(TEXT("录制开始内存"), FString::Printf(TEXT("%.1f MB"), RecordingPerformanceStats.MemoryStartMB), TEXT("开始录制时的物理内存。"));
	AddPerformanceMonitorRow(TEXT("录制当前内存"), FString::Printf(TEXT("%.1f MB"), RecordingPerformanceStats.MemoryCurrentMB), TEXT("当前物理内存。"));
	AddPerformanceMonitorRow(TEXT("录制峰值内存"), FString::Printf(TEXT("%.1f MB"), RecordingPerformanceStats.MemoryPeakMB), TEXT("录制期间观察到的最高物理内存。"));
	AddPerformanceMonitorRow(TEXT("录制内存变化"), FString::Printf(TEXT("%.1f MB"), RecordingPerformanceStats.MemoryDeltaMB), TEXT("当前内存 - 开始录制内存。"));
}

void URecordingPluginSubsystem::OnPerformanceMonitorWindowClosed(const TSharedRef<SWindow>& Window)
{
	(void)Window;

	PerformanceMonitorWindow.Reset();
	PerformanceMonitorRows.Reset();
	StopPerformanceMonitorTicker();
}

void URecordingPluginSubsystem::ResetRecordingPerformanceStats()
{
	RecordingPerformanceStats = FRecordingPerformanceStats();
	RecordingFrameTimeSamplesMs.Reset();
	RecordingPerformanceStartSeconds = 0.0;
	NextRecordingLowStatsRefreshSeconds = 0.0;
	RecordingStopRequestSeconds = 0.0;
	PendingStopRenderFenceStartSeconds = 0.0;
	PendingStopAudioFenceStartSeconds = 0.0;
	PendingStopFinalizeStartSeconds = 0.0;
	RecordingFrameTimeTotalMs = 0.0f;
}

void URecordingPluginSubsystem::BeginRecordingPerformanceStats()
{
	ResetRecordingPerformanceStats();
	RecordingPerformanceStats.bHasRecordingStats = true;
	RecordingPerformanceStats.MemoryStartMB = GetUsedPhysicalMemoryMB();
	RecordingPerformanceStats.MemoryCurrentMB = RecordingPerformanceStats.MemoryStartMB;
	RecordingPerformanceStats.MemoryPeakMB = RecordingPerformanceStats.MemoryStartMB;
	RecordingPerformanceStartSeconds = FPlatformTime::Seconds();
	NextRecordingLowStatsRefreshSeconds = RecordingPerformanceStartSeconds + 0.5;
	StartRecordingPerformanceTicker();
}

void URecordingPluginSubsystem::EndRecordingPerformanceSampling()
{
	StopRecordingPerformanceTicker();
	if (RecordingPerformanceStartSeconds > 0.0)
	{
		RecordingPerformanceStats.RecordingDurationSeconds = static_cast<float>(
			FPlatformTime::Seconds() - RecordingPerformanceStartSeconds);
	}
	RecalculateRecordingFrameStats();
	UpdateRecordingMemoryStats();
}

bool URecordingPluginSubsystem::TickRecordingPerformanceStats(float DeltaTime)
{
	if (!bRecording)
	{
		StopRecordingPerformanceTicker();
		return false;
	}

	if (DeltaTime > 0.0f)
	{
		const float FrameTimeMs = DeltaTime * 1000.0f;
		RecordingFrameTimeSamplesMs.Add(FrameTimeMs);
		RecordingFrameTimeTotalMs += FrameTimeMs;
		RecordingPerformanceStats.SampleCount = RecordingFrameTimeSamplesMs.Num();
		RecordingPerformanceStats.AverageFrameTimeMs =
			RecordingFrameTimeTotalMs / static_cast<float>(RecordingPerformanceStats.SampleCount);
		RecordingPerformanceStats.AverageFPS = RecordingPerformanceStats.AverageFrameTimeMs > 0.0f
			? 1000.0f / RecordingPerformanceStats.AverageFrameTimeMs
			: 0.0f;
		RecordingPerformanceStats.WorstFrameTimeMs = FMath::Max(
			RecordingPerformanceStats.WorstFrameTimeMs, FrameTimeMs);

		const double NowSeconds = FPlatformTime::Seconds();
		if (NowSeconds >= NextRecordingLowStatsRefreshSeconds)
		{
			RecalculateRecordingFrameStats();
			NextRecordingLowStatsRefreshSeconds = NowSeconds + 0.5;
		}
	}
	UpdateRecordingMemoryStats();
	return true;
}

void URecordingPluginSubsystem::RecalculateRecordingFrameStats()
{
	const int32 NumSamples = RecordingFrameTimeSamplesMs.Num();
	RecordingPerformanceStats.SampleCount = NumSamples;
	if (NumSamples <= 0)
	{
		RecordingPerformanceStats.AverageFPS = 0.0f;
		RecordingPerformanceStats.OnePercentLowFPS = 0.0f;
		RecordingPerformanceStats.ZeroPointOnePercentLowFPS = 0.0f;
		RecordingPerformanceStats.AverageFrameTimeMs = 0.0f;
		RecordingPerformanceStats.WorstFrameTimeMs = 0.0f;
		return;
	}

	float TotalFrameMs = 0.0f;
	float WorstFrameMs = 0.0f;
	for (const float FrameMs : RecordingFrameTimeSamplesMs)
	{
		TotalFrameMs += FrameMs;
		WorstFrameMs = FMath::Max(WorstFrameMs, FrameMs);
	}

	const float AverageFrameMs = TotalFrameMs / static_cast<float>(NumSamples);
	RecordingFrameTimeTotalMs = TotalFrameMs;
	RecordingPerformanceStats.AverageFrameTimeMs = AverageFrameMs;
	RecordingPerformanceStats.AverageFPS = AverageFrameMs > 0.0f ? 1000.0f / AverageFrameMs : 0.0f;
	RecordingPerformanceStats.WorstFrameTimeMs = WorstFrameMs;

	TArray<float> SortedFrameMs = RecordingFrameTimeSamplesMs;
	SortedFrameMs.Sort([](const float A, const float B)
	{
		return A > B;
	});

	auto CalculateLowFPS = [&SortedFrameMs, NumSamples](float Percent) -> float
	{
		const int32 Count = FMath::Clamp(FMath::CeilToInt(static_cast<float>(NumSamples) * Percent), 1, NumSamples);
		float TotalSlowFrameMs = 0.0f;
		for (int32 Index = 0; Index < Count; ++Index)
		{
			TotalSlowFrameMs += SortedFrameMs[Index];
		}
		const float AverageSlowFrameMs = TotalSlowFrameMs / static_cast<float>(Count);
		return AverageSlowFrameMs > 0.0f ? 1000.0f / AverageSlowFrameMs : 0.0f;
	};

	RecordingPerformanceStats.OnePercentLowFPS = CalculateLowFPS(0.01f);
	RecordingPerformanceStats.ZeroPointOnePercentLowFPS = CalculateLowFPS(0.001f);
}

void URecordingPluginSubsystem::UpdateRecordingMemoryStats()
{
	const float CurrentMemoryMB = GetUsedPhysicalMemoryMB();
	RecordingPerformanceStats.MemoryCurrentMB = CurrentMemoryMB;
	RecordingPerformanceStats.MemoryPeakMB = FMath::Max(RecordingPerformanceStats.MemoryPeakMB, CurrentMemoryMB);
	RecordingPerformanceStats.MemoryDeltaMB = CurrentMemoryMB - RecordingPerformanceStats.MemoryStartMB;
}

float URecordingPluginSubsystem::GetUsedPhysicalMemoryMB() const
{
	const FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
	return static_cast<float>(static_cast<double>(MemoryStats.UsedPhysical) / 1024.0 / 1024.0);
}

void URecordingPluginSubsystem::StartRecordingPerformanceTicker()
{
	if (!RecordingPerformanceTickerHandle.IsValid())
	{
		RecordingPerformanceTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &URecordingPluginSubsystem::TickRecordingPerformanceStats), 0.0f);
	}
}

void URecordingPluginSubsystem::StopRecordingPerformanceTicker()
{
	if (RecordingPerformanceTickerHandle.IsValid())
	{
		FTSTicker::RemoveTicker(RecordingPerformanceTickerHandle);
		RecordingPerformanceTickerHandle.Reset();
	}
}
