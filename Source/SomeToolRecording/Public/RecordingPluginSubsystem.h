#pragma once

#include "Containers/Ticker.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RecordingPluginSubsystem.generated.h"

class FWMFEncoder;
class FRecordingFrameGrabber;
class FSubmixAudioCapture;
class FViewport;
class SVerticalBox;
class SWindow;
struct FAsyncRecordingStopContext;

struct FWMFEncoderDeleter
{
	void operator()(FWMFEncoder* Ptr) const;
};

struct FRecordingFrameGrabberDeleter
{
	void operator()(FRecordingFrameGrabber* Ptr) const;
};

struct FSubmixAudioCaptureDeleter
{
	void operator()(FSubmixAudioCapture* Ptr) const;
};

struct FAsyncRecordingStopContextDeleter
{
	void operator()(FAsyncRecordingStopContext* Ptr) const;
};

// ── 委托 ──────────────────────────────────────────────────────────────────

/** 录制正常结束时触发，携带输出文件路径 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordingFinished, const FString&, OutputPath);

/** 录制过程中发生错误时触发 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordingError, const FString&, ErrorMessage);

USTRUCT(BlueprintType)
struct SOMETOOLRECORDING_API FRecordingPerformanceStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	bool bHasRecordingStats = false;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	int32 SampleCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float AverageFPS = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float OnePercentLowFPS = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float ZeroPointOnePercentLowFPS = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float AverageFrameTimeMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float WorstFrameTimeMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float RecordingDurationSeconds = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float StartRecordingCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float EncoderInitCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float FrameGrabberInitCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float AudioCaptureInitCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float RenderFenceWaitMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float AudioFenceWaitMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float FinalizeCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float StopTotalCostMs = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float MemoryStartMB = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float MemoryCurrentMB = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float MemoryPeakMB = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "SomeTool|Recording|Perf")
	float MemoryDeltaMB = 0.0f;
};

// ── Subsystem ─────────────────────────────────────────────────────────────

/**
 * 游戏录制 Subsystem。
 * 基于 D3D11 GPU 硬件编码，输出 H.264 MP4。
 *
 * 获取方式（C++ / Blueprint）：
 *   URecordingPluginSubsystem* Rec =
 *       UGameplayStatics::GetGameInstance(this)->GetSubsystem<URecordingPluginSubsystem>();
 */
UCLASS(BlueprintType, meta=(DisplayName="SomeTool Recording Subsystem"))
class SOMETOOLRECORDING_API URecordingPluginSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	URecordingPluginSubsystem();
	virtual ~URecordingPluginSubsystem();

	// ── USubsystem 生命周期 ─────────────────────────────────────────────

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ── 事件 ────────────────────────────────────────────────────────────

	/** 录制完成事件（游戏线程触发） */
	UPROPERTY(BlueprintAssignable, Category = "SomeTool|Recording|Events")
	FOnRecordingFinished OnRecordingFinished;

	/** 录制错误事件（游戏线程触发） */
	UPROPERTY(BlueprintAssignable, Category = "SomeTool|Recording|Events")
	FOnRecordingError OnRecordingError;

	// ── 控制 ────────────────────────────────────────────────────────────

		/**
		 * 开始录制。
		 * 自动检测视口分辨率与当前 RHI（仅支持 D3D11）。
		 *
		 * @param OutputPath   输出文件完整路径（.mp4），目录不存在时自动创建
		 * @param FPS          目标帧率，建议 30 或 60
		 * @param BitrateMbps  编码码率（Mbps），建议 8~16
		 * @return             初始化成功返回 true，失败原因通过 OnRecordingError 广播
		 */
		UFUNCTION(BlueprintCallable, Category = "SomeTool|Recording")
		bool StartRecording(const FString& OutputPath, int32 FPS = 60, int32 BitrateMbps = 8);
	
		/**
		 * 发起停止录制。实际 MP4 finalize 会在后台完成。
		 * 完成后异步触发 OnRecordingFinished。
		 */
		UFUNCTION(BlueprintCallable, Category = "SomeTool|Recording")
		void StopRecording();

	// ── 查询 ────────────────────────────────────────────────────────────

	/** 当前是否正在录制 */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording")
	bool IsRecording() const { return bRecording; }

	/** 录制分辨率（StartRecording 成功后有效） */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording")
	FIntPoint GetResolution() const { return Resolution; }

	/** 已编码帧数 */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording")
	int32 GetFrameCount() const;

	/** 已录制时长（秒） */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording")
	float GetRecordedSeconds() const;

	/** 当前输出文件路径 */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording")
	FString GetOutputPath() const { return CurrentOutputPath; }

	// ── 性能监控窗口 ────────────────────────────────────────────────────

	/** 打开独立性能监控窗口。Shipping 包可用。 */
	UFUNCTION(BlueprintCallable, Category = "SomeTool|Recording|Perf")
	bool OpenPerformanceMonitorWindow();

	/** 关闭独立性能监控窗口。 */
	UFUNCTION(BlueprintCallable, Category = "SomeTool|Recording|Perf")
	void ClosePerformanceMonitorWindow();

	/** 切换独立性能监控窗口显示状态。 */
	UFUNCTION(BlueprintCallable, Category = "SomeTool|Recording|Perf")
	void TogglePerformanceMonitorWindow();

	/** 性能监控窗口当前是否打开。 */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording|Perf")
	bool IsPerformanceMonitorWindowOpen() const;

	/** 获取最近一次录制或当前录制的性能统计。 */
	UFUNCTION(BlueprintPure, Category = "SomeTool|Recording|Perf")
	FRecordingPerformanceStats GetRecordingPerformanceStats() const { return RecordingPerformanceStats; }

private:
	/** 获取当前 D3D11 native device */
	bool DetectRHI(void*& OutNativeDevice) const;

	/** 获取当前游戏视口分辨率 */
	bool GetViewportResolution(int32& OutWidth, int32& OutHeight) const;

	/** 广播错误到游戏线程 */
	void BroadcastError(const FString& Msg);

	/** 视口大小变化回调 */
	void OnViewportResized(FViewport* Viewport, uint32 Unused);

	/** 轮询异步停止状态（游戏线程）。 */
	bool TickPendingStop(float DeltaTime);

	/** 启动/停止异步停止轮询。 */
	void StartPendingStopTicker();
	void StopPendingStopTicker();

	/** 在子系统销毁等场景下同步收尾未完成的停止流程。 */
	void ForceCompletePendingStop(bool bBroadcastFinished);

	/** 更新性能监控窗口文本。 */
	bool TickPerformanceMonitorWindow(float DeltaTime);
	void StartPerformanceMonitorTicker();
	void StopPerformanceMonitorTicker();
	void RefreshPerformanceMonitorWindowRows();
	void AddPerformanceMonitorSection(const FString& Title);
	void AddPerformanceMonitorRow(const FString& Name, const FString& Value, const FString& Description);
	void OnPerformanceMonitorWindowClosed(const TSharedRef<SWindow>& Window);

	void ResetRecordingPerformanceStats();
	void BeginRecordingPerformanceStats();
	void EndRecordingPerformanceSampling();
	bool TickRecordingPerformanceStats(float DeltaTime);
	void RecalculateRecordingFrameStats();
	void UpdateRecordingMemoryStats();
	float GetUsedPhysicalMemoryMB() const;
	void StartRecordingPerformanceTicker();
	void StopRecordingPerformanceTicker();

	// ── 内部状态 ────────────────────────────────────────────────────────

	TUniquePtr<FWMFEncoder, FWMFEncoderDeleter> Encoder;
	TUniquePtr<FRecordingFrameGrabber, FRecordingFrameGrabberDeleter> Grabber;
	TUniquePtr<FSubmixAudioCapture, FSubmixAudioCaptureDeleter> AudioCapture;

	bool      bRecording       = false;
	int32     TargetFPS        = 60;
	FIntPoint Resolution       = FIntPoint::ZeroValue;
	FString   CurrentOutputPath;

	FDelegateHandle ViewportResizedHandle;
	TUniquePtr<FAsyncRecordingStopContext, FAsyncRecordingStopContextDeleter> PendingStopContext;
	FTSTicker::FDelegateHandle PendingStopTickerHandle;

	TWeakPtr<SWindow> PerformanceMonitorWindow;
	TSharedPtr<SVerticalBox> PerformanceMonitorRows;
	FTSTicker::FDelegateHandle PerformanceMonitorTickerHandle;
	bool bPerformanceMonitorShowDescriptions = true;
	int32 PerformanceMonitorRowIndex = 0;

	FRecordingPerformanceStats RecordingPerformanceStats;
	TArray<float> RecordingFrameTimeSamplesMs;
	FTSTicker::FDelegateHandle RecordingPerformanceTickerHandle;
	double RecordingPerformanceStartSeconds = 0.0;
	double NextRecordingLowStatsRefreshSeconds = 0.0;
	double RecordingStopRequestSeconds = 0.0;
	double PendingStopRenderFenceStartSeconds = 0.0;
	double PendingStopAudioFenceStartSeconds = 0.0;
	double PendingStopFinalizeStartSeconds = 0.0;
	float RecordingFrameTimeTotalMs = 0.0f;
};
