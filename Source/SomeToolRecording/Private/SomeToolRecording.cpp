#include "SomeToolRecording.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <mfapi.h>
#include "Windows/HideWindowsPlatformTypes.h"

#define LOCTEXT_NAMESPACE "FSomeToolRecordingModule"

void FSomeToolRecordingModule::StartupModule()
{
	HRESULT Hr = MFStartup(MF_VERSION);
	if (FAILED(Hr))
	{
		UE_LOG(LogTemp, Error, TEXT("SomeToolRecording: MFStartup failed (0x%08X)"), Hr);
	}
}

void FSomeToolRecordingModule::ShutdownModule()
{
	MFShutdown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSomeToolRecordingModule, SomeToolRecording)
