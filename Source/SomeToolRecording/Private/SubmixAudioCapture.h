#pragma once

#include "AudioDeviceHandle.h"
#include "CoreMinimal.h"
#include "ISubmixBufferListener.h"

class FWMFEncoder;

/**
 * 监听 UE Master Submix，把引擎内部混音后的 PCM 音频送入录制编码器。
 */
class FSubmixAudioCapture : public ISubmixBufferListener
{
public:
	FSubmixAudioCapture();
	~FSubmixAudioCapture();

	FSubmixAudioCapture(const FSubmixAudioCapture&) = delete;
	FSubmixAudioCapture& operator=(const FSubmixAudioCapture&) = delete;

	bool Initialize(const FAudioDeviceHandle& InAudioDeviceHandle, FWMFEncoder* InEncoder);
	void Shutdown();
	void BeginShutdown();
	void CompleteShutdown();

	bool IsActive() const { return bActive.Load(); }

	virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData,
	                               int32 NumSamples, int32 InNumChannels, int32 InSampleRate,
	                               double AudioClock) override;
	virtual bool IsRenderingAudio() const override;

private:
	FAudioDeviceHandle AudioDeviceHandle;
	FWMFEncoder* Encoder = nullptr;

	TAtomic<bool> bActive { false };
	int32 SampleRate = 0;
	int32 NumChannels = 0;
	double CaptureStartTimeSeconds = 0.0;
	double NextBufferTimestampSeconds = 0.0;

	uint64 CapturedBufferCount = 0;
	uint64 CapturedFrameCount = 0;
	uint64 WriteFailureCount = 0;
	uint64 FormatMismatchDropCount = 0;
	double CallbackTimeTotalSeconds = 0.0;
	double CallbackTimeMaxSeconds = 0.0;
	double WriteTimeTotalSeconds = 0.0;
	double WriteTimeMaxSeconds = 0.0;
	bool bLoggedFormatMismatch = false;
	bool bListenerRegistered = false;
};
