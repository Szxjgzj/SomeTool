#include "FrameGrabber.h"
#include "WMFEncoder.h"

#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformTime.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/Timespan.h"
#include "RenderingThread.h"
#include "Slate/SceneViewport.h"

DEFINE_LOG_CATEGORY_STATIC(LogRecordingFrameGrabber, Log, All);

// ────────────────────────────────────────────────────────────────────────────

FRecordingFrameGrabber::FRecordingFrameGrabber() = default;

FRecordingFrameGrabber::~FRecordingFrameGrabber()
{
	if (bActive.Load())
	{
		Shutdown();
	}
}

// ────────────────────────────────────────────────────────────────────────────

bool FRecordingFrameGrabber::Initialize(int32 InWidth, int32 InHeight, int32 InTargetFPS, FSceneViewport* InTargetViewport, SWindow* InTargetWindow, FWMFEncoder* InEncoder)
{
	if (bActive.Load())
	{
		UE_LOG(LogRecordingFrameGrabber, Warning, TEXT("Already active, call Shutdown first."));
		return false;
	}

	if (!InEncoder || !InEncoder->IsInitialized())
	{
		UE_LOG(LogRecordingFrameGrabber, Error, TEXT("Encoder is null or not initialized."));
		return false;
	}

	Width = InWidth;
	Height = InHeight;
	TargetFPS = InTargetFPS;
	TargetViewport = InTargetViewport;
	TargetWindow = InTargetWindow;
	Encoder = InEncoder;

	RecordingStartTime = FPlatformTime::Seconds();
	NextFrameIndex = 0;
	FrameCount.Reset();
	RenderCallbackCount = 0;
	DuplicateFrameSubmitCount = 0;
	SourceInvalidSkipCount = 0;
	SourceSizeMismatchCount = 0;
	EncoderSubmitFailureCount = 0;
	RenderCallbackTimeTotalSeconds = 0.0;
	RenderCallbackTimeMaxSeconds = 0.0;
	EncoderSubmitTimeTotalSeconds = 0.0;
	EncoderSubmitTimeMaxSeconds = 0.0;
	bLoggedMissingSourceTexture = false;
	bLoggedSourceSizeMismatch = false;

	if (FSlateApplication::IsInitialized())
	{
		BackBufferDelegateHandle = FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().AddRaw(
			this, &FRecordingFrameGrabber::OnBackBufferReady_RenderThread);
	}
	else
	{
		UE_LOG(LogRecordingFrameGrabber, Error, TEXT("SlateApplication not initialized."));
		Shutdown();
		return false;
	}

	bActive.Store(true);
	UE_LOG(LogRecordingFrameGrabber, Log, TEXT("FrameGrabber initialized: %dx%d @%dfps (DX11 GPU path)"),
	       Width, Height, TargetFPS);
	return true;
}

// ────────────────────────────────────────────────────────────────────────────

void FRecordingFrameGrabber::Shutdown()
{
	BeginShutdown();
	FlushRenderingCommands();
	CompleteShutdown();
}

void FRecordingFrameGrabber::BeginShutdown()
{
	bActive.Store(false);

	if (BackBufferDelegateHandle.IsValid() && FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().Remove(BackBufferDelegateHandle);
		BackBufferDelegateHandle.Reset();
	}
}

void FRecordingFrameGrabber::CompleteShutdown()
{
	const double RecordingDurationSeconds = FMath::Max(0.0, FPlatformTime::Seconds() - RecordingStartTime);
	const uint64 SubmitAttemptCount = static_cast<uint64>(FrameCount.GetValue()) + EncoderSubmitFailureCount;
	const double AverageCallbackMs = RenderCallbackCount > 0
		? (RenderCallbackTimeTotalSeconds * 1000.0 / static_cast<double>(RenderCallbackCount))
		: 0.0;
	const double AverageSubmitMs = SubmitAttemptCount > 0
		? (EncoderSubmitTimeTotalSeconds * 1000.0 / static_cast<double>(SubmitAttemptCount))
		: 0.0;
	const double RenderThreadDutyPercent = RecordingDurationSeconds > 0.0
		? (RenderCallbackTimeTotalSeconds / RecordingDurationSeconds) * 100.0
		: 0.0;

	Encoder = nullptr;
	TargetViewport = nullptr;
	TargetWindow = nullptr;
	UE_LOG(LogRecordingFrameGrabber, Log,
	       TEXT("FrameGrabber shutdown. Captured=%d duplicateSubmits=%llu sourceInvalidSkips=%llu sizeMismatchFrames=%llu encoderSubmitFailures=%llu"),
	       FrameCount.GetValue(),
	       DuplicateFrameSubmitCount,
	       SourceInvalidSkipCount,
	       SourceSizeMismatchCount,
	       EncoderSubmitFailureCount);
	UE_LOG(LogRecordingFrameGrabber, Log,
	       TEXT("FrameGrabber perf: duration=%.3fs renderCallbacks=%llu submitAttempts=%llu avgCallback=%.3fms maxCallback=%.3fms avgSubmit=%.3fms maxSubmit=%.3fms renderThreadDuty=%.2f%%"),
	       RecordingDurationSeconds,
	       RenderCallbackCount,
	       SubmitAttemptCount,
	       AverageCallbackMs,
	       RenderCallbackTimeMaxSeconds * 1000.0,
	       AverageSubmitMs,
	       EncoderSubmitTimeMaxSeconds * 1000.0,
	       RenderThreadDutyPercent);
}

// ────────────────────────────────────────────────────────────────────────────

void FRecordingFrameGrabber::OnBackBufferReady_RenderThread(SWindow& SlateWindow, const FTexture2DRHIRef& BackBuffer)
{
	const double CallbackStartSeconds = FPlatformTime::Seconds();

	if (!bActive.Load() || !Encoder || !BackBuffer.IsValid())
	{
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		++RenderCallbackCount;
		RenderCallbackTimeTotalSeconds += CallbackElapsedSeconds;
		RenderCallbackTimeMaxSeconds = FMath::Max(RenderCallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	if (TargetWindow && &SlateWindow != TargetWindow)
	{
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		++RenderCallbackCount;
		RenderCallbackTimeTotalSeconds += CallbackElapsedSeconds;
		RenderCallbackTimeMaxSeconds = FMath::Max(RenderCallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	auto IsDirectEncoderMatch = [this](const FTexture2DRHIRef& Texture) -> bool
	{
		return Texture.IsValid() &&
		       Texture->GetFormat() == PF_B8G8R8A8 &&
		       Texture->GetSizeX() == Width &&
		       Texture->GetSizeY() == Height;
	};

	auto IsSameSize = [this](const FTexture2DRHIRef& Texture) -> bool
	{
		return Texture.IsValid() &&
		       Texture->GetSizeX() == Width &&
		       Texture->GetSizeY() == Height;
	};

	FTexture2DRHIRef ViewportRenderTarget;
	if (TargetViewport)
	{
		ViewportRenderTarget = TargetViewport->GetRenderTargetTexture();
	}

	FTexture2DRHIRef SourceTexture = BackBuffer;
	if (!IsDirectEncoderMatch(SourceTexture) && IsDirectEncoderMatch(ViewportRenderTarget))
	{
		SourceTexture = ViewportRenderTarget;
	}
	else if (!IsSameSize(SourceTexture) && IsSameSize(ViewportRenderTarget))
	{
		SourceTexture = ViewportRenderTarget;
	}

	if (!SourceTexture.IsValid())
	{
		++SourceInvalidSkipCount;
		if (!bLoggedMissingSourceTexture)
		{
			UE_LOG(LogRecordingFrameGrabber, Warning, TEXT("Skipping capture because source texture is invalid."));
			bLoggedMissingSourceTexture = true;
		}
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		++RenderCallbackCount;
		RenderCallbackTimeTotalSeconds += CallbackElapsedSeconds;
		RenderCallbackTimeMaxSeconds = FMath::Max(RenderCallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	const int32 SourceWidth = SourceTexture->GetSizeX();
	const int32 SourceHeight = SourceTexture->GetSizeY();
	if (SourceWidth != Width || SourceHeight != Height)
	{
		++SourceSizeMismatchCount;
		if (!bLoggedSourceSizeMismatch)
		{
			UE_LOG(LogRecordingFrameGrabber, Warning,
			       TEXT("Source backbuffer is %dx%d while recording size is %dx%d. Falling back to encoder-side conversion for mismatched frames."),
			       SourceWidth, SourceHeight, Width, Height);
			bLoggedSourceSizeMismatch = true;
		}
	}

	const int32 SubmitCount = ComputeSubmitCount();
	if (SubmitCount <= 0)
	{
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		++RenderCallbackCount;
		RenderCallbackTimeTotalSeconds += CallbackElapsedSeconds;
		RenderCallbackTimeMaxSeconds = FMath::Max(RenderCallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	if (SubmitCount > 1)
	{
		DuplicateFrameSubmitCount += static_cast<uint64>(SubmitCount - 1);
	}

	const int64 FrameDurationTicks = ETimespan::TicksPerSecond / TargetFPS;
	for (int32 i = 0; i < SubmitCount; ++i)
	{
		const int64 FrameIdx = NextFrameIndex - SubmitCount + i;
		const int64 TimestampTicks = FrameIdx * FrameDurationTicks;

		const double SubmitStartSeconds = FPlatformTime::Seconds();
		const int64 WriteHr = Encoder->WriteSample(SourceTexture, TimestampTicks, FrameDurationTicks);
		const double SubmitElapsedSeconds = FPlatformTime::Seconds() - SubmitStartSeconds;
		EncoderSubmitTimeTotalSeconds += SubmitElapsedSeconds;
		EncoderSubmitTimeMaxSeconds = FMath::Max(EncoderSubmitTimeMaxSeconds, SubmitElapsedSeconds);
		if (WriteHr >= 0)
		{
			FrameCount.Increment();
		}
		else
		{
			++EncoderSubmitFailureCount;
		}
	}

	const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
	++RenderCallbackCount;
	RenderCallbackTimeTotalSeconds += CallbackElapsedSeconds;
	RenderCallbackTimeMaxSeconds = FMath::Max(RenderCallbackTimeMaxSeconds, CallbackElapsedSeconds);
}

// ────────────────────────────────────────────────────────────────────────────

int32 FRecordingFrameGrabber::ComputeSubmitCount()
{
	const double Now = FPlatformTime::Seconds();
	const double Elapsed = Now - RecordingStartTime;
	const int64 ExpectedFrameIndex = static_cast<int64>(Elapsed * TargetFPS);

	if (ExpectedFrameIndex < NextFrameIndex)
	{
		return 0;
	}

	int32 Count = static_cast<int32>(ExpectedFrameIndex - NextFrameIndex + 1);
	Count = FMath::Clamp(Count, 1, 3);

	NextFrameIndex = ExpectedFrameIndex + 1;
	return Count;
}
