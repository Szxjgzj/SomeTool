#include "WMFEncoder.h"

#include "Async/Async.h"
#include "CodecPacket.h"
#include "CommonRenderResources.h"
#include "HAL/Event.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Timespan.h"
#include "Modules/ModuleManager.h"
#include "PipelineStateCache.h"
#include "RendererInterface.h"
#include "RHI.h"
#include "RHICommandList.h"
#include "RHIStaticStates.h"
#include "RHIUtilities.h"
#include "RenderingThread.h"
#include "ScreenRendering.h"
#include "ShaderCore.h"
#include "VideoCommon.h"
#include "VideoEncoder.h"
#include "VideoEncoderFactory.h"
#include "VideoEncoderInput.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <wrl/client.h>
#include "Windows/HideWindowsPlatformTypes.h"

using Microsoft::WRL::ComPtr;

DEFINE_LOG_CATEGORY_STATIC(LogWMFEncoder, Log, All);

namespace
{
	FCriticalSection GSharedVideoEncoderInputLock;
	TSharedPtr<AVEncoder::FVideoEncoderInput> GSharedVideoEncoderInput;
	void* GSharedVideoEncoderNativeDevice = nullptr;
	bool GSharedVideoEncoderUsesSharedDevice = false;
}

// ────────────────────────────────────────────────────────────────────────────

FWMFEncoder::FWMFEncoder() = default;

FWMFEncoder::~FWMFEncoder()
{
	if (bInitialized)
	{
		Finalize();
	}
}

// ────────────────────────────────────────────────────────────────────────────

bool FWMFEncoder::Initialize(const FString& InOutputPath, int32 InWidth, int32 InHeight,
                             int32 InFPS, int32 InBitrateMbps, void* NativeDevice,
                             int32 InAudioSampleRate, int32 InAudioChannels)
{
	if (bInitialized)
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("Already initialized, call Finalize first."));
		return false;
	}

	Width = static_cast<uint32>(InWidth);
	Height = static_cast<uint32>(InHeight);
	FrameRate = static_cast<uint32>(InFPS);
	FrameDurationTicks = ETimespan::TicksPerSecond / FMath::Max(1, InFPS);
	AudioSampleRate = InAudioSampleRate > 0 ? static_cast<uint32>(InAudioSampleRate) : 0;
	AudioChannels = InAudioChannels > 0 ? static_cast<uint32>(InAudioChannels) : 0;
	AudioBitrate = 0;
	SubmittedFrameCount = 0;
	PacketsWritten = 0;
	InputBufferBackpressureCount = 0;
	PacketWriteFailureCount = 0;
	DirectCopyCount = 0;
	ConversionCopyCount = 0;
	AudioBuffersWritten = 0;
	AudioSampleFramesWritten = 0;
	AudioWriteFailureCount = 0;
	AudioQueueOverflowDropCount = 0;
	AudioWriterPeakQueueDepth = 0;
	VideoWriterPeakQueueDepth = 0;
	QueuedVideoFrameCount.Reset();
	QueuedAudioBufferCount.Reset();
	bLoggedAudioQueueOverflow = false;
	bLoggedConversionPath = false;
	InputBufferSourceFormat = PF_Unknown;
	bInputBuffersUseRenderTargetConversion = false;

	if (AudioSampleRate > 0 && AudioChannels > 0)
	{
		if ((AudioSampleRate != 44100 && AudioSampleRate != 48000) ||
		    (AudioChannels != 1 && AudioChannels != 2 && AudioChannels != 6))
		{
			UE_LOG(LogWMFEncoder, Warning,
			       TEXT("AAC audio disabled because %uHz / %uch is unsupported by WMF AAC."),
			       AudioSampleRate, AudioChannels);
			AudioSampleRate = 0;
			AudioChannels = 0;
		}
		else
		{
			AudioBitrate = DefaultAudioBitrate;
		}
	}

	FModuleManager::Get().LoadModulePtr<IModuleInterface>(TEXT("AVEncoder"));
	FModuleManager::Get().LoadModulePtr<IModuleInterface>(TEXT("EncoderAMF"));
	FModuleManager::Get().LoadModulePtr<IModuleInterface>(TEXT("EncoderNVENC"));

	if (!InitializeMp4Writer(InOutputPath, InWidth, InHeight, InFPS, InBitrateMbps,
	                         static_cast<int32>(AudioSampleRate),
	                         static_cast<int32>(AudioChannels),
	                         static_cast<int32>(AudioBitrate)) ||
	    !InitializeVideoEncoder(NativeDevice, InWidth, InHeight, InFPS, InBitrateMbps))
	{
		ReleaseResources();
		return false;
	}

	if (!StartVideoWriter())
	{
		ReleaseResources();
		return false;
	}

	bInitialized = true;
	if (HasAudioStream())
	{
		StartAudioWriter();
	}

	if (HasAudioStream())
	{
		UE_LOG(LogWMFEncoder, Log,
		       TEXT("Encoder initialized: %dx%d @%dfps %dMbps D3D11 GPU + AAC %uHz %uch -> %s"),
		       InWidth, InHeight, InFPS, InBitrateMbps, AudioSampleRate, AudioChannels, *InOutputPath);
	}
	else
	{
		UE_LOG(LogWMFEncoder, Log, TEXT("Encoder initialized: %dx%d @%dfps %dMbps D3D11 GPU -> %s"),
		       InWidth, InHeight, InFPS, InBitrateMbps, *InOutputPath);
	}
	return true;
}

// ────────────────────────────────────────────────────────────────────────────

bool FWMFEncoder::InitializeMp4Writer(const FString& InOutputPath, int32 InWidth, int32 InHeight,
                                      int32 InFPS, int32 InBitrateMbps,
                                      int32 InAudioSampleRate, int32 InAudioChannels, int32 InAudioBitrate)
{
	HRESULT Hr = MFCreateSinkWriterFromURL(*InOutputPath, nullptr, nullptr, &SinkWriter);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("MFCreateSinkWriterFromURL failed: 0x%08X (Path: %s)"),
		       Hr, *InOutputPath);
		return false;
	}

	ComPtr<IMFMediaType> MediaType;
	Hr = MFCreateMediaType(&MediaType);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("MFCreateMediaType failed: 0x%08X"), Hr);
		return false;
	}

	MediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	MediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
	MediaType->SetUINT32(MF_MT_AVG_BITRATE, static_cast<UINT32>(InBitrateMbps) * 1000000u);
	MFSetAttributeRatio(MediaType.Get(), MF_MT_FRAME_RATE, InFPS, 1);
	MFSetAttributeSize(MediaType.Get(), MF_MT_FRAME_SIZE, InWidth, InHeight);
	MFSetAttributeRatio(MediaType.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
	MediaType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);

	DWORD LocalVideoStreamIndex = 0;
	Hr = SinkWriter->AddStream(MediaType.Get(), &LocalVideoStreamIndex);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("AddStream (H264) failed: 0x%08X"), Hr);
		return false;
	}
	VideoStreamIndex = LocalVideoStreamIndex;

	Hr = SinkWriter->SetInputMediaType(VideoStreamIndex, MediaType.Get(), nullptr);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("SetInputMediaType (H264) failed: 0x%08X"), Hr);
		return false;
	}

	if (InAudioSampleRate > 0 && InAudioChannels > 0 && InAudioBitrate > 0)
	{
		ComPtr<IMFMediaType> AudioOutputType;
		Hr = MFCreateMediaType(&AudioOutputType);
		if (FAILED(Hr))
		{
			UE_LOG(LogWMFEncoder, Error, TEXT("MFCreateMediaType (AAC output) failed: 0x%08X"), Hr);
			return false;
		}

		AudioOutputType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		AudioOutputType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_AAC);
		AudioOutputType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
		AudioOutputType->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, static_cast<UINT32>(InAudioSampleRate));
		AudioOutputType->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, static_cast<UINT32>(InAudioChannels));
		AudioOutputType->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, static_cast<UINT32>(InAudioBitrate / 8));

		DWORD LocalAudioStreamIndex = 0;
		Hr = SinkWriter->AddStream(AudioOutputType.Get(), &LocalAudioStreamIndex);
		if (FAILED(Hr))
		{
			UE_LOG(LogWMFEncoder, Error, TEXT("AddStream (AAC) failed: 0x%08X"), Hr);
			return false;
		}
		AudioStreamIndex = LocalAudioStreamIndex;

		ComPtr<IMFMediaType> AudioInputType;
		Hr = MFCreateMediaType(&AudioInputType);
		if (FAILED(Hr))
		{
			UE_LOG(LogWMFEncoder, Error, TEXT("MFCreateMediaType (PCM input) failed: 0x%08X"), Hr);
			return false;
		}

		const UINT32 AudioBlockAlignment = static_cast<UINT32>(InAudioChannels * sizeof(int16));
		AudioInputType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		AudioInputType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		AudioInputType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
		AudioInputType->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, static_cast<UINT32>(InAudioSampleRate));
		AudioInputType->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, static_cast<UINT32>(InAudioChannels));
		AudioInputType->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT, AudioBlockAlignment);
		AudioInputType->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND,
		                          static_cast<UINT32>(InAudioSampleRate) * AudioBlockAlignment);

		Hr = SinkWriter->SetInputMediaType(AudioStreamIndex, AudioInputType.Get(), nullptr);
		if (FAILED(Hr))
		{
			UE_LOG(LogWMFEncoder, Error, TEXT("SetInputMediaType (PCM) failed: 0x%08X"), Hr);
			return false;
		}
	}

	Hr = SinkWriter->BeginWriting();
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("BeginWriting failed: 0x%08X"), Hr);
		return false;
	}

	return true;
}

bool FWMFEncoder::InitializeVideoEncoder(void* NativeDevice, int32 InWidth, int32 InHeight,
                                         int32 InFPS, int32 InBitrateMbps)
{
	if (!NativeDevice)
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("Native D3D11 device is null."));
		return false;
	}

	const bool bUseSharedDevice = IsRHIDeviceAMD();
	{
		FScopeLock Lock(&GSharedVideoEncoderInputLock);
		if (!GSharedVideoEncoderInput.IsValid() ||
		    GSharedVideoEncoderNativeDevice != NativeDevice ||
		    GSharedVideoEncoderUsesSharedDevice != bUseSharedDevice)
		{
			GSharedVideoEncoderInput = AVEncoder::FVideoEncoderInput::CreateForD3D11(NativeDevice, true, bUseSharedDevice);
			GSharedVideoEncoderNativeDevice = NativeDevice;
			GSharedVideoEncoderUsesSharedDevice = bUseSharedDevice;

			if (!GSharedVideoEncoderInput.IsValid())
			{
				UE_LOG(LogWMFEncoder, Error, TEXT("CreateForD3D11 failed."));
				return false;
			}

			UE_LOG(LogWMFEncoder, Log, TEXT("Created shared AVEncoder input (shared-device=%s)."),
			       bUseSharedDevice ? TEXT("true") : TEXT("false"));
		}
		else
		{
			UE_LOG(LogWMFEncoder, Verbose, TEXT("Reusing shared AVEncoder input from previous recording session."));
		}

		VideoEncoderInput = GSharedVideoEncoderInput;
	}

	if (!VideoEncoderInput.IsValid())
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("Shared AVEncoder input is invalid."));
		return false;
	}

	AVEncoder::FVideoEncoder::FLayerConfig LayerConfig;
	LayerConfig.Width = InWidth;
	LayerConfig.Height = InHeight;
	LayerConfig.MaxFramerate = InFPS;
	LayerConfig.MaxBitrate = InBitrateMbps * 1000000;
	LayerConfig.TargetBitrate = InBitrateMbps * 1000000;
	LayerConfig.H264Profile = AVEncoder::FVideoEncoder::H264Profile::MAIN;

	const TArray<AVEncoder::FVideoEncoderInfo>& AvailableEncoders = AVEncoder::FVideoEncoderFactory::Get().GetAvailable();
	if (AvailableEncoders.Num() == 0)
	{
		UE_LOG(LogWMFEncoder, Error,
		       TEXT("No GPU H264 encoders are available. Enable the HardwareEncoders plugin and use a supported GPU driver."));
		return false;
	}

	for (const AVEncoder::FVideoEncoderInfo& EncoderInfo : AvailableEncoders)
	{
		if (EncoderInfo.CodecType != AVEncoder::ECodecType::H264)
		{
			continue;
		}

		VideoEncoder = AVEncoder::FVideoEncoderFactory::Get().Create(EncoderInfo.ID, VideoEncoderInput, LayerConfig);
		if (VideoEncoder.IsValid())
		{
			UE_LOG(LogWMFEncoder, Log, TEXT("Selected GPU H264 encoder id=%u"), EncoderInfo.ID);
			break;
		}
	}

	if (!VideoEncoder.IsValid())
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("Failed to create a GPU H264 encoder for D3D11."));
		return false;
	}

	VideoEncoder->SetOnEncodedPacket(
		[this](uint32 LayerIndex, const TSharedPtr<AVEncoder::FVideoEncoderInputFrame> InputFrame, const AVEncoder::FCodecPacket& Packet)
		{
			HandleEncodedVideoPacket(LayerIndex, InputFrame, Packet);
		});

	bVideoEncoderInitialized = true;
	return true;
}

int64 FWMFEncoder::WriteSample(const FTexture2DRHIRef& SourceTexture, int64 TimestampTicks, int64 DurationTicks)
{
	check(IsInRenderingThread());

	if (!bInitialized || !SinkWriter || !VideoEncoder.IsValid() || !VideoEncoderInput.IsValid() || !bVideoWriterRunning.Load())
	{
		return E_NOT_VALID_STATE;
	}

	if (!SourceTexture.IsValid())
	{
		return E_POINTER;
	}

	FrameDurationTicks = DurationTicks;

	if (!InitializeInputBuffers_RenderThread(SourceTexture))
	{
		return E_FAIL;
	}

	TSharedPtr<AVEncoder::FVideoEncoderInputFrame> InputFrame;
	int32 InputBufferSlotIndex = INDEX_NONE;
	if (!ObtainInputBuffer_RenderThread(InputFrame, InputBufferSlotIndex))
	{
		++InputBufferBackpressureCount;
		if (!bLoggedNoAvailableInputBuffer)
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("Dropping frame because all encoder input buffers are busy."));
			bLoggedNoAvailableInputBuffer = true;
		}
		return MF_E_NOTACCEPTING;
	}
	bLoggedNoAvailableInputBuffer = false;

	InputFrame->SetTimestampUs(TimestampTicks);
	InputFrame->SetTimestampRTP(TimestampTicks);
	if (!InputBuffers.IsValidIndex(InputBufferSlotIndex) ||
	    !CopyTexture(SourceTexture, InputBuffers[InputBufferSlotIndex]))
	{
		InputFrame->Release();
		return E_FAIL;
	}

	FEncoderBufferSlot& InputBufferSlot = InputBuffers[InputBufferSlotIndex];
	if (!InputBufferSlot.EncodeFence.IsValid())
	{
		InputBufferSlot.EncodeFence = RHICreateGPUFence(TEXT("RecordingPluginVideoEncodeFence"));
		if (!InputBufferSlot.EncodeFence.IsValid())
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("Failed to create GPU fence for encoder input slot %d."), InputBufferSlotIndex);
			InputFrame->Release();
			return E_FAIL;
		}
	}

	InputBufferSlot.EncodeFence->Clear();
	FRHICommandListImmediate& RHICmdList = FRHICommandListExecutor::GetImmediateCommandList();
	RHICmdList.WriteGPUFence(InputBufferSlot.EncodeFence);

	FQueuedVideoFrame QueuedFrame;
	QueuedFrame.InputFrame = InputFrame;
	QueuedFrame.EncodeFence = InputBufferSlot.EncodeFence;
	QueuedFrame.bForceKeyFrame = (SubmittedFrameCount == 0);
	QueuedVideoFrames.Enqueue(MoveTemp(QueuedFrame));
	QueuedVideoFrameCount.Increment();
	VideoWriterPeakQueueDepth = FMath::Max<uint64>(
		VideoWriterPeakQueueDepth,
		static_cast<uint64>(QueuedVideoFrameCount.GetValue()));

	if (VideoWriterWakeEvent)
	{
		VideoWriterWakeEvent->Trigger();
	}

	++SubmittedFrameCount;
	return S_OK;
}

int64 FWMFEncoder::WriteAudioSamples(const int16* SampleData, int32 NumSamples, int64 TimestampTicks, int64 DurationTicks)
{
	if (!SampleData || NumSamples <= 0)
	{
		return E_INVALIDARG;
	}

	if (!bInitialized || !SinkWriter || !HasAudioStream() || !bAudioWriterRunning.Load())
	{
		return E_NOT_VALID_STATE;
	}

	if (QueuedAudioBufferCount.GetValue() >= MaxQueuedAudioBuffers)
	{
		++AudioQueueOverflowDropCount;
		if (!bLoggedAudioQueueOverflow)
		{
			bLoggedAudioQueueOverflow = true;
			UE_LOG(LogWMFEncoder, Warning,
			       TEXT("Dropping audio buffer because the async audio writer queue is full (%d buffers)."),
			       MaxQueuedAudioBuffers);
		}
		return MF_E_NOTACCEPTING;
	}

	FQueuedAudioBuffer QueuedBuffer;
	QueuedBuffer.SampleData.Append(SampleData, NumSamples);
	QueuedBuffer.TimestampTicks = TimestampTicks;
	QueuedBuffer.DurationTicks = DurationTicks;

	QueuedAudioBuffers.Enqueue(MoveTemp(QueuedBuffer));
	QueuedAudioBufferCount.Increment();
	AudioWriterPeakQueueDepth = FMath::Max<uint64>(
		AudioWriterPeakQueueDepth,
		static_cast<uint64>(QueuedAudioBufferCount.GetValue()));

	if (AudioWriterWakeEvent)
	{
		AudioWriterWakeEvent->Trigger();
	}

	return S_OK;
}

int64 FWMFEncoder::WriteAudioSamples_Immediate(const int16* SampleData, int32 NumSamples, int64 TimestampTicks, int64 DurationTicks)
{
	FScopeLock Lock(&WriteLock);

	if (!bInitialized || !SinkWriter || !HasAudioStream())
	{
		return E_NOT_VALID_STATE;
	}

	const uint32 BufferSizeBytes = static_cast<uint32>(NumSamples * sizeof(int16));
	ComPtr<IMFMediaBuffer> Buffer;
	HRESULT Hr = MFCreateAlignedMemoryBuffer(BufferSizeBytes, MF_1_BYTE_ALIGNMENT, &Buffer);
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("MFCreateAlignedMemoryBuffer (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	BYTE* BufferData = nullptr;
	Hr = Buffer->Lock(&BufferData, nullptr, nullptr);
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::Lock (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	FMemory::Memcpy(BufferData, SampleData, BufferSizeBytes);
	Hr = Buffer->Unlock();
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::Unlock (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	Hr = Buffer->SetCurrentLength(BufferSizeBytes);
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::SetCurrentLength (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	ComPtr<IMFSample> Sample;
	Hr = MFCreateSample(&Sample);
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("MFCreateSample (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	Hr = Sample->AddBuffer(Buffer.Get());
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFSample::AddBuffer (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	Sample->SetSampleTime(TimestampTicks);
	Sample->SetSampleDuration(DurationTicks);

	Hr = SinkWriter->WriteSample(AudioStreamIndex, Sample.Get());
	if (FAILED(Hr))
	{
		++AudioWriteFailureCount;
		UE_LOG(LogWMFEncoder, Warning, TEXT("SinkWriter->WriteSample (audio) failed: 0x%08X"), Hr);
		return Hr;
	}

	++AudioBuffersWritten;
	AudioSampleFramesWritten += static_cast<uint64>(NumSamples / FMath::Max(1u, AudioChannels));
	return S_OK;
}

bool FWMFEncoder::StartVideoWriter()
{
	if (VideoWriterTask.IsValid())
	{
		return true;
	}

	if (!VideoEncoder.IsValid())
	{
		return false;
	}

	VideoWriterWakeEvent = FPlatformProcess::GetSynchEventFromPool(false);
	if (!VideoWriterWakeEvent)
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("Failed to create the async video writer event."));
		return false;
	}

	bVideoWriterRunning.Store(true);
	VideoWriterTask = Async(EAsyncExecution::Thread, [this]()
	{
		VideoWriterLoop();
	});
	return true;
}

void FWMFEncoder::StopVideoWriter()
{
	bVideoWriterRunning.Store(false);

	if (VideoWriterWakeEvent)
	{
		VideoWriterWakeEvent->Trigger();
	}

	if (VideoWriterTask.IsValid())
	{
		VideoWriterTask.Wait();
		VideoWriterTask = TFuture<void>();
	}

	FQueuedVideoFrame QueuedFrame;
	while (QueuedVideoFrames.Dequeue(QueuedFrame))
	{
		if (QueuedFrame.InputFrame.IsValid())
		{
			QueuedFrame.InputFrame->Release();
		}
		QueuedFrame.InputFrame.Reset();
		QueuedFrame.EncodeFence.SafeRelease();
	}
	QueuedVideoFrameCount.Reset();

	if (VideoWriterWakeEvent)
	{
		FPlatformProcess::ReturnSynchEventToPool(VideoWriterWakeEvent);
		VideoWriterWakeEvent = nullptr;
	}
}

void FWMFEncoder::VideoWriterLoop()
{
	FQueuedVideoFrame PendingFrame;
	bool bHasPendingFrame = false;

	while (bVideoWriterRunning.Load() || bHasPendingFrame || QueuedVideoFrameCount.GetValue() > 0)
	{
		if (!bHasPendingFrame)
		{
			if (!QueuedVideoFrames.Dequeue(PendingFrame))
			{
				if (VideoWriterWakeEvent)
				{
					VideoWriterWakeEvent->Wait(10);
				}
				continue;
			}

			QueuedVideoFrameCount.Decrement();
			bHasPendingFrame = PendingFrame.InputFrame.IsValid();
			if (!bHasPendingFrame)
			{
				PendingFrame.EncodeFence.SafeRelease();
			}
		}

		if (!bHasPendingFrame)
		{
			continue;
		}

		if (PendingFrame.EncodeFence.IsValid() &&
		    (PendingFrame.EncodeFence->NumPendingWriteCommands.GetValue() != 0 || !PendingFrame.EncodeFence->Poll()))
		{
			if (VideoWriterWakeEvent)
			{
				VideoWriterWakeEvent->Wait(1);
			}
			else
			{
				FPlatformProcess::SleepNoStats(0.001f);
			}
			continue;
		}

		if (VideoEncoder.IsValid())
		{
			AVEncoder::FVideoEncoder::FEncodeOptions EncodeOptions;
			EncodeOptions.bForceKeyFrame = PendingFrame.bForceKeyFrame;
			VideoEncoder->Encode(PendingFrame.InputFrame, EncodeOptions);
		}
		else
		{
			PendingFrame.InputFrame->Release();
		}

		PendingFrame.InputFrame.Reset();
		PendingFrame.EncodeFence.SafeRelease();
		PendingFrame.bForceKeyFrame = false;
		bHasPendingFrame = false;
	}
}

void FWMFEncoder::StartAudioWriter()
{
	if (!HasAudioStream() || AudioWriterTask.IsValid())
	{
		return;
	}

	AudioWriterWakeEvent = FPlatformProcess::GetSynchEventFromPool(false);
	if (!AudioWriterWakeEvent)
	{
		UE_LOG(LogWMFEncoder, Error, TEXT("Failed to create the async audio writer event."));
		return;
	}

	bAudioWriterRunning.Store(true);
	AudioWriterTask = Async(EAsyncExecution::Thread, [this]()
	{
		AudioWriterLoop();
	});
}

void FWMFEncoder::StopAudioWriter()
{
	bAudioWriterRunning.Store(false);

	if (AudioWriterWakeEvent)
	{
		AudioWriterWakeEvent->Trigger();
	}

	if (AudioWriterTask.IsValid())
	{
		AudioWriterTask.Wait();
		AudioWriterTask = TFuture<void>();
	}

	if (AudioWriterWakeEvent)
	{
		FPlatformProcess::ReturnSynchEventToPool(AudioWriterWakeEvent);
		AudioWriterWakeEvent = nullptr;
	}
}

void FWMFEncoder::AudioWriterLoop()
{
	while (bAudioWriterRunning.Load() || QueuedAudioBufferCount.GetValue() > 0)
	{
		FQueuedAudioBuffer QueuedBuffer;
		if (QueuedAudioBuffers.Dequeue(QueuedBuffer))
		{
			QueuedAudioBufferCount.Decrement();
			WriteAudioSamples_Immediate(
				QueuedBuffer.SampleData.GetData(),
				QueuedBuffer.SampleData.Num(),
				QueuedBuffer.TimestampTicks,
				QueuedBuffer.DurationTicks);
			continue;
		}

		if (AudioWriterWakeEvent)
		{
			AudioWriterWakeEvent->Wait(10);
		}
	}
}

bool FWMFEncoder::CopyTexture(const FTexture2DRHIRef& SourceTexture, FEncoderBufferSlot& DestinationSlot)
{
	check(IsInRenderingThread());

	if (!SourceTexture.IsValid() || !DestinationSlot.Texture.IsValid())
	{
		return false;
	}

	FRHICommandListImmediate& RHICmdList = FRHICommandListExecutor::GetImmediateCommandList();
	FTexture2DRHIRef& DestinationTexture = DestinationSlot.Texture;

	if (SourceTexture->GetFormat() == DestinationTexture->GetFormat() &&
	    SourceTexture->GetSizeXY() == DestinationTexture->GetSizeXY())
	{
		++DirectCopyCount;
		TransitionAndCopyTexture(RHICmdList, SourceTexture, DestinationTexture, {});
		return true;
	}

	++ConversionCopyCount;
	if (!bLoggedConversionPath)
	{
		UE_LOG(LogWMFEncoder, Log,
		       TEXT("Using encoder conversion path for source %dx%d %s -> %dx%d %s."),
		       SourceTexture->GetSizeX(),
		       SourceTexture->GetSizeY(),
		       GetPixelFormatString(SourceTexture->GetFormat()),
		       DestinationTexture->GetSizeX(),
		       DestinationTexture->GetSizeY(),
		       GetPixelFormatString(DestinationTexture->GetFormat()));
		bLoggedConversionPath = true;
	}

	if (bInputBuffersUseRenderTargetConversion)
	{
		IRendererModule* RendererModule = &FModuleManager::GetModuleChecked<IRendererModule>(TEXT("Renderer"));

		FRHIRenderPassInfo RPInfo(DestinationTexture, ERenderTargetActions::DontLoad_Store);
		RHICmdList.Transition(FRHITransitionInfo(DestinationTexture, ERHIAccess::Unknown, ERHIAccess::RTV));
		RHICmdList.BeginRenderPass(RPInfo, TEXT("RecordingPluginConvertToEncoderSurface"));
		{
			RHICmdList.SetViewport(0, 0, 0.0f, static_cast<float>(DestinationTexture->GetSizeX()),
			                       static_cast<float>(DestinationTexture->GetSizeY()), 1.0f);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

			FGlobalShaderMap* ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
			TShaderMapRef<FScreenVS> VertexShader(ShaderMap);
			TShaderMapRef<FScreenPS> PixelShader(ShaderMap);

			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
			GraphicsPSOInit.PrimitiveType = PT_TriangleList;

			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, 0);

			const bool bSameSize = (DestinationTexture->GetDesc().Extent == SourceTexture->GetDesc().Extent);
			FRHISamplerState* PixelSampler = bSameSize ? TStaticSamplerState<SF_Point>::GetRHI() : TStaticSamplerState<SF_Bilinear>::GetRHI();

			SetShaderParametersLegacyPS(RHICmdList, PixelShader, PixelSampler, SourceTexture);

			RendererModule->DrawRectangle(
				RHICmdList,
				0, 0,
				static_cast<float>(DestinationTexture->GetSizeX()),
				static_cast<float>(DestinationTexture->GetSizeY()),
				0, 0,
				1, 1,
				DestinationTexture->GetSizeXY(),
				FIntPoint(1, 1),
				VertexShader,
				EDRF_Default);
		}
		RHICmdList.EndRenderPass();
		RHICmdList.Transition(FRHITransitionInfo(DestinationTexture, ERHIAccess::RTV, ERHIAccess::SRVMask));
		return true;
	}

	if (!DestinationSlot.ConversionTexture.IsValid())
	{
		const FRHITextureCreateDesc ConversionDesc =
			FRHITextureCreateDesc::Create2D(TEXT("RecordingPluginEncoderConversion"), Width, Height, PF_B8G8R8A8)
			.SetFlags(ETextureCreateFlags::RenderTargetable | ETextureCreateFlags::ShaderResource)
			.SetInitialState(ERHIAccess::RTV);

		DestinationSlot.ConversionTexture = RHICreateTexture(ConversionDesc);
		if (!DestinationSlot.ConversionTexture.IsValid())
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("Failed to allocate encoder conversion texture."));
			return false;
		}
	}

	FTexture2DRHIRef& ConversionTexture = DestinationSlot.ConversionTexture;
	IRendererModule* RendererModule = &FModuleManager::GetModuleChecked<IRendererModule>(TEXT("Renderer"));

	FRHIRenderPassInfo RPInfo(ConversionTexture, ERenderTargetActions::Load_Store);
	RHICmdList.Transition(FRHITransitionInfo(ConversionTexture, ERHIAccess::Unknown, ERHIAccess::RTV));
	RHICmdList.BeginRenderPass(RPInfo, TEXT("RecordingPluginCopyBackbuffer"));
	{
		RHICmdList.SetViewport(0, 0, 0.0f, static_cast<float>(ConversionTexture->GetSizeX()),
		                       static_cast<float>(ConversionTexture->GetSizeY()), 1.0f);

		FGraphicsPipelineStateInitializer GraphicsPSOInit;
		RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
		GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
		GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
		GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

		FGlobalShaderMap* ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
		TShaderMapRef<FScreenVS> VertexShader(ShaderMap);
		TShaderMapRef<FScreenPS> PixelShader(ShaderMap);

		GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
		GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
		GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
		GraphicsPSOInit.PrimitiveType = PT_TriangleList;

		SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, 0);

		const bool bSameSize = (DestinationTexture->GetDesc().Extent == SourceTexture->GetDesc().Extent);
		FRHISamplerState* PixelSampler = bSameSize ? TStaticSamplerState<SF_Point>::GetRHI() : TStaticSamplerState<SF_Bilinear>::GetRHI();

		SetShaderParametersLegacyPS(RHICmdList, PixelShader, PixelSampler, SourceTexture);

		RendererModule->DrawRectangle(
			RHICmdList,
			0, 0,
			static_cast<float>(ConversionTexture->GetSizeX()),
			static_cast<float>(ConversionTexture->GetSizeY()),
			0, 0,
			1, 1,
			ConversionTexture->GetSizeXY(),
			FIntPoint(1, 1),
			VertexShader,
			EDRF_Default);
	}
	RHICmdList.EndRenderPass();
	RHICmdList.Transition(FRHITransitionInfo(ConversionTexture, ERHIAccess::RTV, ERHIAccess::SRVMask));
	TransitionAndCopyTexture(RHICmdList, ConversionTexture, DestinationTexture, {});
	return true;
}

bool FWMFEncoder::InitializeInputBuffers_RenderThread(const FTexture2DRHIRef& SourceTexture)
{
	check(IsInRenderingThread());

	if (InputBuffers.Num() > 0)
	{
		return true;
	}

	InputBufferSourceFormat = SourceTexture.IsValid() ? SourceTexture->GetFormat() : PF_Unknown;
	bInputBuffersUseRenderTargetConversion =
		!SourceTexture.IsValid() ||
		SourceTexture->GetFormat() != PF_B8G8R8A8 ||
		SourceTexture->GetSizeX() != Width ||
		SourceTexture->GetSizeY() != Height;

	// Keep a session-local set of encoder frames so AMF never sees stale pooled frame bindings.
	for (int32 BufferIndex = 0; BufferIndex < NumBufferedFrames; ++BufferIndex)
	{
		AVEncoder::FVideoEncoderInputFrame* const RawFrame = VideoEncoderInput->CreateBuffer(
			[this](const AVEncoder::FVideoEncoderInputFrame* ReleasedFrame)
			{
				HandleInputBufferReleased(ReleasedFrame);
			});
		if (!RawFrame)
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("CreateBuffer failed for encoder input slot %d."), BufferIndex);
			DestroyInputBuffers();
			return false;
		}

		RawFrame->SetWidth(Width);
		RawFrame->SetHeight(Height);

		const FRHITextureCreateDesc Desc =
			FRHITextureCreateDesc::Create2D(TEXT("RecordingPluginEncoderBackBuffer"), Width, Height, PF_B8G8R8A8)
			.SetFlags(ETextureCreateFlags::Shared | ETextureCreateFlags::ShaderResource |
			          (bInputBuffersUseRenderTargetConversion ? ETextureCreateFlags::RenderTargetable : ETextureCreateFlags::None))
			.SetInitialState(bInputBuffersUseRenderTargetConversion ? ERHIAccess::RTV : ERHIAccess::CopyDest);

		FTexture2DRHIRef Texture = RHICreateTexture(Desc);
		if (!Texture.IsValid())
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("Failed to allocate encoder backbuffer for slot %d."), BufferIndex);
			VideoEncoderInput->DestroyBuffer(RawFrame);
			DestroyInputBuffers();
			return false;
		}

		RawFrame->SetTexture(
			static_cast<ID3D11Texture2D*>(Texture->GetNativeResource()),
			AVEncoder::FVideoEncoderInputFrame::FReleaseD3D11TextureCallback());

		if (RawFrame->GetD3D11().EncoderTexture == nullptr)
		{
			UE_LOG(LogWMFEncoder, Warning, TEXT("Failed to bind D3D11 encoder texture for slot %d."), BufferIndex);
			VideoEncoderInput->DestroyBuffer(RawFrame);
			DestroyInputBuffers();
			return false;
		}

		FEncoderBufferSlot Slot;
		Slot.RawFrame = RawFrame;
		Slot.SharedFrame = MakeShareable(
			RawFrame,
			[](AVEncoder::FVideoEncoderInputFrame* FrameToDelete)
			{
				(void)FrameToDelete;
			});
		Slot.Texture = Texture;
		Slot.bAvailable = true;

		InputBufferLookup.Add(RawFrame, InputBuffers.Num());
		InputBuffers.Add(MoveTemp(Slot));
	}

	UE_LOG(LogWMFEncoder, Log,
	       TEXT("Initialized %d encoder input buffers for %ux%u frames (source=%s, path=%s)."),
	       InputBuffers.Num(),
	       Width,
	       Height,
	       GetPixelFormatString(InputBufferSourceFormat),
	       bInputBuffersUseRenderTargetConversion ? TEXT("render-conversion") : TEXT("direct-copy"));
	return true;
}

bool FWMFEncoder::ObtainInputBuffer_RenderThread(TSharedPtr<AVEncoder::FVideoEncoderInputFrame>& OutInputFrame,
                                                 int32& OutSlotIndex)
{
	check(IsInRenderingThread());

	FScopeLock Lock(&InputBuffersLock);
	for (int32 SlotIndex = 0; SlotIndex < InputBuffers.Num(); ++SlotIndex)
	{
		FEncoderBufferSlot& Slot = InputBuffers[SlotIndex];
		if (Slot.bAvailable && Slot.SharedFrame.IsValid() && Slot.Texture.IsValid())
		{
			Slot.bAvailable = false;
			OutInputFrame = Slot.SharedFrame;
			OutSlotIndex = SlotIndex;
			return true;
		}
	}

	OutInputFrame.Reset();
	OutSlotIndex = INDEX_NONE;
	return false;
}

void FWMFEncoder::HandleInputBufferReleased(const AVEncoder::FVideoEncoderInputFrame* ReleasedFrame)
{
	if (!ReleasedFrame)
	{
		return;
	}

	FScopeLock Lock(&InputBuffersLock);
	const int32* SlotIndex = InputBufferLookup.Find(ReleasedFrame);
	if (!SlotIndex || !InputBuffers.IsValidIndex(*SlotIndex))
	{
		return;
	}

	FEncoderBufferSlot& Slot = InputBuffers[*SlotIndex];
	if (!Slot.bAvailable)
	{
		Slot.bAvailable = true;
	}
}

void FWMFEncoder::HandleEncodedVideoPacket(uint32 LayerIndex,
                                           const TSharedPtr<AVEncoder::FVideoEncoderInputFrame> InputFrame,
                                           const AVEncoder::FCodecPacket& Packet)
{
	(void)LayerIndex;

	if (!InputFrame.IsValid())
	{
		return;
	}

	if (!WriteVideoPacket(*InputFrame, Packet))
	{
		++PacketWriteFailureCount;
	}
	InputFrame->Release();
}

bool FWMFEncoder::WriteVideoPacket(const AVEncoder::FVideoEncoderInputFrame& InputFrame,
                                   const AVEncoder::FCodecPacket& Packet)
{
	FScopeLock Lock(&WriteLock);

	if (!bInitialized || !SinkWriter)
	{
		return false;
	}

	if (!Packet.Data.IsValid() || Packet.DataSize == 0)
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("Encoded packet is empty."));
		return false;
	}

	ComPtr<IMFMediaBuffer> Buffer;
	HRESULT Hr = MFCreateAlignedMemoryBuffer(Packet.DataSize, MF_1_BYTE_ALIGNMENT, &Buffer);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("MFCreateAlignedMemoryBuffer failed: 0x%08X"), Hr);
		return false;
	}

	BYTE* BufferData = nullptr;
	Hr = Buffer->Lock(&BufferData, nullptr, nullptr);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::Lock failed: 0x%08X"), Hr);
		return false;
	}

	FMemory::Memcpy(BufferData, Packet.Data.Get(), Packet.DataSize);
	Hr = Buffer->Unlock();
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::Unlock failed: 0x%08X"), Hr);
		return false;
	}

	Hr = Buffer->SetCurrentLength(Packet.DataSize);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFMediaBuffer::SetCurrentLength failed: 0x%08X"), Hr);
		return false;
	}

	ComPtr<IMFSample> Sample;
	Hr = MFCreateSample(&Sample);
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("MFCreateSample failed: 0x%08X"), Hr);
		return false;
	}

	Hr = Sample->AddBuffer(Buffer.Get());
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("IMFSample::AddBuffer failed: 0x%08X"), Hr);
		return false;
	}

	Sample->SetSampleTime(InputFrame.GetTimestampUs());
	Sample->SetSampleDuration(FrameDurationTicks);
	if (Packet.IsKeyFrame)
	{
		Sample->SetUINT32(MFSampleExtension_CleanPoint, 1);
	}

	Hr = SinkWriter->WriteSample(VideoStreamIndex, Sample.Get());
	if (FAILED(Hr))
	{
		UE_LOG(LogWMFEncoder, Warning, TEXT("SinkWriter->WriteSample failed: 0x%08X"), Hr);
		return false;
	}

	++PacketsWritten;
	return true;
}

// ────────────────────────────────────────────────────────────────────────────

void FWMFEncoder::Finalize()
{
	if (!bInitialized)
	{
		return;
	}

	StopVideoWriter();

	if (VideoEncoder.IsValid())
	{
		VideoEncoder->Shutdown();
		VideoEncoder->ClearOnEncodedPacket();
	}

	StopAudioWriter();

	{
		FScopeLock Lock(&WriteLock);
		if (SinkWriter)
		{
			if (PacketsWritten == 0)
			{
				UE_LOG(LogWMFEncoder, Error, TEXT("No encoded packets were written. The output MP4 will be empty."));
			}

				const HRESULT Hr = SinkWriter->Finalize();
				if (FAILED(Hr))
				{
					UE_LOG(LogWMFEncoder, Error, TEXT("SinkWriter->Finalize failed: 0x%08X"), Hr);
				}
				else
				{
					UE_LOG(LogWMFEncoder, Log,
					       TEXT("SinkWriter finalized successfully. videoPackets=%llu submittedFrames=%llu backpressureDrops=%llu videoPacketWriteFailures=%llu directCopies=%llu conversionCopies=%llu videoQueuePeak=%llu audioBuffers=%llu audioFrames=%llu audioWriteFailures=%llu audioQueueDrops=%llu audioQueuePeak=%llu"),
					       PacketsWritten,
					       SubmittedFrameCount,
					       InputBufferBackpressureCount,
					       PacketWriteFailureCount,
					       DirectCopyCount,
					       ConversionCopyCount,
					       VideoWriterPeakQueueDepth,
					       AudioBuffersWritten,
					       AudioSampleFramesWritten,
					       AudioWriteFailureCount,
					       AudioQueueOverflowDropCount,
					       AudioWriterPeakQueueDepth);
				}
			}
		}

	ReleaseResources();
	bInitialized = false;
}

// ────────────────────────────────────────────────────────────────────────────

void FWMFEncoder::DestroyInputBuffers()
{
	FScopeLock Lock(&InputBuffersLock);

	if (!VideoEncoderInput.IsValid())
	{
		InputBufferLookup.Empty();
		InputBuffers.Empty();
		return;
	}

	for (FEncoderBufferSlot& Slot : InputBuffers)
	{
		if (Slot.RawFrame)
		{
			VideoEncoderInput->DestroyBuffer(Slot.RawFrame);
			Slot.RawFrame = nullptr;
		}

		Slot.SharedFrame.Reset();
		Slot.Texture.SafeRelease();
		Slot.ConversionTexture.SafeRelease();
		Slot.EncodeFence.SafeRelease();
		Slot.bAvailable = false;
	}

	InputBufferLookup.Empty();
	InputBuffers.Empty();
}

void FWMFEncoder::ReleaseResources()
{
	StopVideoWriter();
	StopAudioWriter();

	DestroyInputBuffers();

	VideoEncoder.Reset();

	if (VideoEncoderInput.IsValid())
	{
		VideoEncoderInput->Flush();
	}
	VideoEncoderInput.Reset();

	if (SinkWriter)
	{
		SinkWriter->Release();
		SinkWriter = nullptr;
	}

	VideoStreamIndex = 0;
	AudioStreamIndex = InvalidStreamIndex;
	AudioSampleRate = 0;
	AudioChannels = 0;
	AudioBitrate = 0;
	bVideoEncoderInitialized = false;
	SubmittedFrameCount = 0;
	PacketsWritten = 0;
	InputBufferBackpressureCount = 0;
	PacketWriteFailureCount = 0;
	DirectCopyCount = 0;
	ConversionCopyCount = 0;
	VideoWriterPeakQueueDepth = 0;
	AudioBuffersWritten = 0;
	AudioSampleFramesWritten = 0;
	AudioWriteFailureCount = 0;
	AudioQueueOverflowDropCount = 0;
	AudioWriterPeakQueueDepth = 0;
	FrameDurationTicks = 0;
	QueuedVideoFrameCount.Reset();
	QueuedAudioBufferCount.Reset();
	InputBufferSourceFormat = PF_Unknown;
	bLoggedNoAvailableInputBuffer = false;
	bLoggedAudioQueueOverflow = false;
	bLoggedConversionPath = false;
	bInputBuffersUseRenderTargetConversion = false;
}
