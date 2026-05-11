#pragma once

#include "Async/Future.h"
#include "Containers/Map.h"
#include "Containers/Queue.h"
#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"
#include "HAL/ThreadSafeCounter.h"
#include "RHIResources.h"
#include "Templates/SharedPointer.h"
#include "Templates/UniquePtr.h"

class FEvent;
struct IMFSinkWriter;

namespace AVEncoder
{
	class FCodecPacket;
	class FVideoEncoder;
	class FVideoEncoderInput;
	class FVideoEncoderInputFrame;
}

/**
 * DX11 GPU 编码器封装。
 * 使用 AVEncoder 做 H.264 硬件编码，再用 WMF SinkWriter 复用 MP4 封装。
 */
class FWMFEncoder
{
public:
	FWMFEncoder();
	~FWMFEncoder();

	FWMFEncoder(const FWMFEncoder&) = delete;
	FWMFEncoder& operator=(const FWMFEncoder&) = delete;

	/**
	 * 初始化编码器。
	 * @param InOutputPath   MP4 输出路径
	 * @param InWidth        视频宽度
	 * @param InHeight       视频高度
	 * @param InFPS          目标帧率
	 * @param InBitrateMbps  码率 (Mbps)
	 * @param NativeDevice   D3D11 native device
	 * @return 成功返回 true
	 */
	bool Initialize(const FString& InOutputPath, int32 InWidth, int32 InHeight,
	                int32 InFPS, int32 InBitrateMbps, void* NativeDevice,
	                int32 InAudioSampleRate = 0, int32 InAudioChannels = 0);

	/**
	 * 在渲染线程提交一帧 GPU 纹理给编码器。
	 * @param SourceTexture  源纹理（通常为游戏窗口 BackBuffer）
	 * @param TimestampTicks 帧时间戳（FTimespan tick = 100ns）
	 * @param DurationTicks  帧持续时间（FTimespan tick = 100ns）
	 * @return HRESULT
	 */
	int64 WriteSample(const FTexture2DRHIRef& SourceTexture, int64 TimestampTicks, int64 DurationTicks);
	int64 WriteAudioSamples(const int16* SampleData, int32 NumSamples, int64 TimestampTicks, int64 DurationTicks);

	/** 结束编码，写入 moov atom。线程安全。 */
	void Finalize();

	/** 编码器是否已初始化 */
	bool IsInitialized() const { return bInitialized; }
	bool HasAudioStream() const { return AudioStreamIndex != InvalidStreamIndex; }
	int32 GetAudioSampleRate() const { return static_cast<int32>(AudioSampleRate); }
	int32 GetAudioChannelCount() const { return static_cast<int32>(AudioChannels); }

private:
	struct FQueuedVideoFrame
	{
		TSharedPtr<AVEncoder::FVideoEncoderInputFrame> InputFrame;
		FGPUFenceRHIRef EncodeFence;
		bool bForceKeyFrame = false;
	};

	struct FQueuedAudioBuffer
	{
		TArray<int16> SampleData;
		int64 TimestampTicks = 0;
		int64 DurationTicks = 0;
	};

	struct FEncoderBufferSlot
	{
		AVEncoder::FVideoEncoderInputFrame* RawFrame = nullptr;
		TSharedPtr<AVEncoder::FVideoEncoderInputFrame> SharedFrame;
		FTexture2DRHIRef Texture;
		FTexture2DRHIRef ConversionTexture;
		FGPUFenceRHIRef EncodeFence;
		bool bAvailable = false;
	};

	bool InitializeMp4Writer(const FString& InOutputPath, int32 InWidth, int32 InHeight,
	                         int32 InFPS, int32 InBitrateMbps,
	                         int32 InAudioSampleRate, int32 InAudioChannels, int32 InAudioBitrate);
	bool InitializeVideoEncoder(void* NativeDevice, int32 InWidth, int32 InHeight,
	                            int32 InFPS, int32 InBitrateMbps);
	bool CopyTexture(const FTexture2DRHIRef& SourceTexture, FEncoderBufferSlot& DestinationSlot);
	bool InitializeInputBuffers_RenderThread(const FTexture2DRHIRef& SourceTexture);
	bool ObtainInputBuffer_RenderThread(TSharedPtr<AVEncoder::FVideoEncoderInputFrame>& OutInputFrame,
	                                    int32& OutSlotIndex);
	void HandleInputBufferReleased(const AVEncoder::FVideoEncoderInputFrame* ReleasedFrame);
	void HandleEncodedVideoPacket(uint32 LayerIndex,
	                              const TSharedPtr<AVEncoder::FVideoEncoderInputFrame> InputFrame,
	                              const AVEncoder::FCodecPacket& Packet);
	bool WriteVideoPacket(const AVEncoder::FVideoEncoderInputFrame& InputFrame,
	                      const AVEncoder::FCodecPacket& Packet);
	int64 WriteAudioSamples_Immediate(const int16* SampleData, int32 NumSamples, int64 TimestampTicks, int64 DurationTicks);
	bool StartVideoWriter();
	void StopVideoWriter();
	void VideoWriterLoop();
	void StartAudioWriter();
	void StopAudioWriter();
	void AudioWriterLoop();
	void DestroyInputBuffers();
	void ReleaseResources();

	IMFSinkWriter* SinkWriter = nullptr;
	uint32 VideoStreamIndex = 0;
	uint32 AudioStreamIndex = InvalidStreamIndex;
	uint32 Width = 0;
	uint32 Height = 0;
	uint32 FrameRate = 0;
	uint32 AudioSampleRate = 0;
	uint32 AudioChannels = 0;
	uint32 AudioBitrate = 0;
	int64 FrameDurationTicks = 0;
	uint64 SubmittedFrameCount = 0;
	uint64 PacketsWritten = 0;
	uint64 InputBufferBackpressureCount = 0;
	uint64 PacketWriteFailureCount = 0;
	uint64 DirectCopyCount = 0;
	uint64 ConversionCopyCount = 0;
	uint64 AudioBuffersWritten = 0;
	uint64 AudioSampleFramesWritten = 0;
	uint64 AudioWriteFailureCount = 0;
	uint64 AudioQueueOverflowDropCount = 0;
	uint64 AudioWriterPeakQueueDepth = 0;
	EPixelFormat InputBufferSourceFormat = PF_Unknown;
	bool bInitialized = false;
	bool bVideoEncoderInitialized = false;
	bool bInputBuffersUseRenderTargetConversion = false;

	TSharedPtr<AVEncoder::FVideoEncoderInput> VideoEncoderInput;
	TUniquePtr<AVEncoder::FVideoEncoder> VideoEncoder;
	TArray<FEncoderBufferSlot> InputBuffers;
	TMap<const AVEncoder::FVideoEncoderInputFrame*, int32> InputBufferLookup;
	TQueue<FQueuedVideoFrame, EQueueMode::Spsc> QueuedVideoFrames;
	TQueue<FQueuedAudioBuffer, EQueueMode::Mpsc> QueuedAudioBuffers;

	FCriticalSection InputBuffersLock;
	FCriticalSection WriteLock;
	FThreadSafeCounter QueuedVideoFrameCount;
	FThreadSafeCounter QueuedAudioBufferCount;
	TFuture<void> VideoWriterTask;
	FEvent* VideoWriterWakeEvent = nullptr;
	TFuture<void> AudioWriterTask;
	FEvent* AudioWriterWakeEvent = nullptr;
	TAtomic<bool> bVideoWriterRunning { false };
	TAtomic<bool> bAudioWriterRunning { false };
	uint64 VideoWriterPeakQueueDepth = 0;
	bool bLoggedNoAvailableInputBuffer = false;
	bool bLoggedAudioQueueOverflow = false;
	bool bLoggedConversionPath = false;

	static constexpr uint32 InvalidStreamIndex = MAX_uint32;
	static constexpr int32 DefaultAudioBitrate = 192000;
	static constexpr int32 NumBufferedFrames = 3;
	static constexpr int32 MaxQueuedAudioBuffers = 64;
};
