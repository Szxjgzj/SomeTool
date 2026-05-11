#include "SubmixAudioCapture.h"

#include "AudioDevice.h"
#include "AudioThread.h"
#include "HAL/PlatformTime.h"
#include "Misc/Timespan.h"
#include "SampleBuffer.h"
#include "WMFEncoder.h"

DEFINE_LOG_CATEGORY_STATIC(LogSubmixAudioCapture, Log, All);

FSubmixAudioCapture::FSubmixAudioCapture() = default;

FSubmixAudioCapture::~FSubmixAudioCapture()
{
	if (bActive.Load())
	{
		Shutdown();
	}
}

bool FSubmixAudioCapture::Initialize(const FAudioDeviceHandle& InAudioDeviceHandle, FWMFEncoder* InEncoder)
{
	if (bActive.Load())
	{
		UE_LOG(LogSubmixAudioCapture, Warning, TEXT("Audio capture is already active."));
		return false;
	}

	if (!InAudioDeviceHandle.IsValid())
	{
		UE_LOG(LogSubmixAudioCapture, Warning, TEXT("Audio capture skipped because no valid audio device was found."));
		return false;
	}

	if (!InEncoder || !InEncoder->IsInitialized() || !InEncoder->HasAudioStream())
	{
		UE_LOG(LogSubmixAudioCapture, Warning, TEXT("Audio capture skipped because encoder audio stream is unavailable."));
		return false;
	}

	AudioDeviceHandle = InAudioDeviceHandle;
	Encoder = InEncoder;
	SampleRate = InEncoder->GetAudioSampleRate();
	NumChannels = InEncoder->GetAudioChannelCount();
	CaptureStartTimeSeconds = FPlatformTime::Seconds();
	NextBufferTimestampSeconds = 0.0;
	CapturedBufferCount = 0;
	CapturedFrameCount = 0;
	WriteFailureCount = 0;
	FormatMismatchDropCount = 0;
	CallbackTimeTotalSeconds = 0.0;
	CallbackTimeMaxSeconds = 0.0;
	WriteTimeTotalSeconds = 0.0;
	WriteTimeMaxSeconds = 0.0;
	bLoggedFormatMismatch = false;

	bActive.Store(true);
	AudioDeviceHandle->RegisterSubmixBufferListener(this);
	bListenerRegistered = true;

	UE_LOG(LogSubmixAudioCapture, Log, TEXT("Audio capture initialized: Master Submix -> %dHz %dch AAC"),
	       SampleRate, NumChannels);
	return true;
}

void FSubmixAudioCapture::Shutdown()
{
	BeginShutdown();

	FAudioCommandFence AudioFence;
	AudioFence.BeginFence();
	AudioFence.Wait();

	CompleteShutdown();
}

void FSubmixAudioCapture::BeginShutdown()
{
	bActive.Store(false);

	if (bListenerRegistered && AudioDeviceHandle.IsValid())
	{
		AudioDeviceHandle->UnregisterSubmixBufferListener(this);
		bListenerRegistered = false;
	}
}

void FSubmixAudioCapture::CompleteShutdown()
{
	if (AudioDeviceHandle.IsValid())
	{
		AudioDeviceHandle.Reset();
	}
	bListenerRegistered = false;

	Encoder = nullptr;

	const double RecordingDurationSeconds = FMath::Max(0.0, FPlatformTime::Seconds() - CaptureStartTimeSeconds);
	const uint64 ProcessedBufferCount = CapturedBufferCount + FormatMismatchDropCount + WriteFailureCount;
	const double AverageCallbackMs = ProcessedBufferCount > 0
		? (CallbackTimeTotalSeconds * 1000.0 / static_cast<double>(ProcessedBufferCount))
		: 0.0;
	const double AverageWriteMs = CapturedBufferCount > 0
		? (WriteTimeTotalSeconds * 1000.0 / static_cast<double>(CapturedBufferCount))
		: 0.0;
	const double AudioThreadDutyPercent = RecordingDurationSeconds > 0.0
		? (CallbackTimeTotalSeconds / RecordingDurationSeconds) * 100.0
		: 0.0;

	UE_LOG(LogSubmixAudioCapture, Log,
	       TEXT("Audio capture shutdown. Buffers=%llu frames=%llu formatDrops=%llu writeFailures=%llu"),
	       CapturedBufferCount,
	       CapturedFrameCount,
	       FormatMismatchDropCount,
	       WriteFailureCount);
	UE_LOG(LogSubmixAudioCapture, Log,
	       TEXT("Audio capture perf: duration=%.3fs callbacks=%llu avgCallback=%.3fms maxCallback=%.3fms avgSubmit=%.3fms maxSubmit=%.3fms audioThreadDuty=%.2f%%"),
	       RecordingDurationSeconds,
	       ProcessedBufferCount,
	       AverageCallbackMs,
	       CallbackTimeMaxSeconds * 1000.0,
	       AverageWriteMs,
	       WriteTimeMaxSeconds * 1000.0,
	       AudioThreadDutyPercent);

	SampleRate = 0;
	NumChannels = 0;
	CaptureStartTimeSeconds = 0.0;
	NextBufferTimestampSeconds = 0.0;
}

void FSubmixAudioCapture::OnNewSubmixBuffer(const USoundSubmix* /*OwningSubmix*/, float* AudioData,
                                            int32 NumSamples, int32 InNumChannels, int32 InSampleRate,
                                            double /*AudioClock*/)
{
	const double CallbackStartSeconds = FPlatformTime::Seconds();

	if (!bActive.Load() || !Encoder || !AudioData)
	{
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		CallbackTimeTotalSeconds += CallbackElapsedSeconds;
		CallbackTimeMaxSeconds = FMath::Max(CallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	if (NumSamples <= 0 || InNumChannels <= 0 || InSampleRate <= 0 || (NumSamples % InNumChannels) != 0)
	{
		++FormatMismatchDropCount;
		if (!bLoggedFormatMismatch)
		{
			bLoggedFormatMismatch = true;
			UE_LOG(LogSubmixAudioCapture, Warning,
			       TEXT("Dropping audio buffer because its layout is invalid. samples=%d channels=%d sampleRate=%d"),
			       NumSamples, InNumChannels, InSampleRate);
		}
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		CallbackTimeTotalSeconds += CallbackElapsedSeconds;
		CallbackTimeMaxSeconds = FMath::Max(CallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	if (InSampleRate != SampleRate)
	{
		++FormatMismatchDropCount;
		if (!bLoggedFormatMismatch)
		{
			bLoggedFormatMismatch = true;
			UE_LOG(LogSubmixAudioCapture, Warning,
			       TEXT("Dropping audio buffer because sample rate changed from %dHz to %dHz."),
			       SampleRate, InSampleRate);
		}
		const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
		CallbackTimeTotalSeconds += CallbackElapsedSeconds;
		CallbackTimeMaxSeconds = FMath::Max(CallbackTimeMaxSeconds, CallbackElapsedSeconds);
		return;
	}

	Audio::FAlignedFloatBuffer FloatData;
	FloatData.Append(AudioData, NumSamples);

	Audio::TSampleBuffer<float> FloatBuffer(FloatData, InNumChannels, InSampleRate);
	if (FloatBuffer.GetNumChannels() != NumChannels)
	{
		FloatBuffer.MixBufferToChannels(NumChannels);
	}
	FloatBuffer.Clamp();

	Audio::TSampleBuffer<int16> PCM16Buffer;
	PCM16Buffer = FloatBuffer;
	const double BufferDurationSeconds = FloatBuffer.GetSampleDuration();
	const int64 TimestampTicks = FMath::RoundToInt64(NextBufferTimestampSeconds * static_cast<double>(ETimespan::TicksPerSecond));
	const int64 DurationTicks = FMath::Max<int64>(
		1,
		FMath::RoundToInt64(BufferDurationSeconds * static_cast<double>(ETimespan::TicksPerSecond)));

	const double WriteStartSeconds = FPlatformTime::Seconds();
	const int64 WriteHr = Encoder->WriteAudioSamples(PCM16Buffer.GetData(), PCM16Buffer.GetNumSamples(), TimestampTicks, DurationTicks);
	const double WriteElapsedSeconds = FPlatformTime::Seconds() - WriteStartSeconds;
	WriteTimeTotalSeconds += WriteElapsedSeconds;
	WriteTimeMaxSeconds = FMath::Max(WriteTimeMaxSeconds, WriteElapsedSeconds);
	NextBufferTimestampSeconds += BufferDurationSeconds;

	if (WriteHr >= 0)
	{
		++CapturedBufferCount;
		CapturedFrameCount += static_cast<uint64>(PCM16Buffer.GetNumFrames());
	}
	else
	{
		++WriteFailureCount;
		if (WriteFailureCount == 1)
		{
			UE_LOG(LogSubmixAudioCapture, Warning, TEXT("WriteAudioSamples failed: 0x%08X"), static_cast<uint32>(WriteHr));
		}
	}

	const double CallbackElapsedSeconds = FPlatformTime::Seconds() - CallbackStartSeconds;
	CallbackTimeTotalSeconds += CallbackElapsedSeconds;
	CallbackTimeMaxSeconds = FMath::Max(CallbackTimeMaxSeconds, CallbackElapsedSeconds);
}

bool FSubmixAudioCapture::IsRenderingAudio() const
{
	return bActive.Load();
}
