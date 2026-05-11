#pragma once

#include "CoreMinimal.h"
#include "HAL/ThreadSafeCounter.h"
#include "RHIResources.h"

class FWMFEncoder;
class FSceneViewport;
class SWindow;

/**
 * 帧捕获器。
 * 注册 OnBackBufferReadyToPresent 回调，在渲染线程中将目标窗口 BackBuffer
 * 提交给 DX11 GPU 编码器。
 */
class FRecordingFrameGrabber
{
public:
	FRecordingFrameGrabber();
	~FRecordingFrameGrabber();

	FRecordingFrameGrabber(const FRecordingFrameGrabber&) = delete;
	FRecordingFrameGrabber& operator=(const FRecordingFrameGrabber&) = delete;

	/**
	 * 初始化帧捕获器。
	 * @param InWidth       捕获宽度
	 * @param InHeight      捕获高度
	 * @param InTargetFPS   目标帧率
	 * @param InTargetWindow 目标游戏窗口，仅捕获该窗口的 BackBuffer
	 * @param InEncoder     编码器指针（生命周期由调用方管理）
	 * @return 成功返回 true
	 */
	bool Initialize(int32 InWidth, int32 InHeight, int32 InTargetFPS, FSceneViewport* InTargetViewport, SWindow* InTargetWindow, FWMFEncoder* InEncoder);

	/** 停止捕获，取消回调注册，等待渲染线程完成后输出统计。 */
	void Shutdown();
	void BeginShutdown();
	void CompleteShutdown();

	/** 是否已初始化 */
	bool IsActive() const { return bActive.Load(); }

	/** 已提交帧数 */
	int32 GetFrameCount() const { return FrameCount.GetValue(); }

private:
	/** 渲染线程回调：BackBuffer 就绪时触发 */
	void OnBackBufferReady_RenderThread(SWindow& SlateWindow, const FTexture2DRHIRef& BackBuffer);

	/**
	 * 帧率规整：返回本帧应该提交的次数。
	 * 0 = 跳帧（游戏帧率 > 目标帧率）
	 * 1 = 正常提交
	 * 2+ = 重复帧（游戏帧率 < 目标帧率，上限 3）
	 */
	int32 ComputeSubmitCount();

	// ── 配置 ────────────────────────────────────────────────────────────
	int32 Width = 0;
	int32 Height = 0;
	int32 TargetFPS = 60;
	TAtomic<bool> bActive { false };

	// ── 帧率规整 ────────────────────────────────────────────────────────
	double RecordingStartTime = 0.0;
	int64 NextFrameIndex = 0;

	// ── 计数 ────────────────────────────────────────────────────────────
	FThreadSafeCounter FrameCount;
	uint64 RenderCallbackCount = 0;
	uint64 DuplicateFrameSubmitCount = 0;
	uint64 SourceInvalidSkipCount = 0;
	uint64 SourceSizeMismatchCount = 0;
	uint64 EncoderSubmitFailureCount = 0;
	double RenderCallbackTimeTotalSeconds = 0.0;
	double RenderCallbackTimeMaxSeconds = 0.0;
	double EncoderSubmitTimeTotalSeconds = 0.0;
	double EncoderSubmitTimeMaxSeconds = 0.0;

	// ── 依赖 ────────────────────────────────────────────────────────────
	FWMFEncoder* Encoder = nullptr;
	FSceneViewport* TargetViewport = nullptr;
	SWindow* TargetWindow = nullptr;

	// ── 委托句柄 ────────────────────────────────────────────────────────
	FDelegateHandle BackBufferDelegateHandle;

	bool bLoggedMissingSourceTexture = false;
	bool bLoggedSourceSizeMismatch = false;
};
