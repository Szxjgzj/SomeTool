#include "SomeToolAsyncTask.h"

DEFINE_LOG_CATEGORY(LogSomeToolAsyncTask);

void FSomeToolAsyncTaskModule::StartupModule()
{
}

void FSomeToolAsyncTaskModule::ShutdownModule()
{
}

IMPLEMENT_MODULE(FSomeToolAsyncTaskModule, SomeToolAsyncTask)
