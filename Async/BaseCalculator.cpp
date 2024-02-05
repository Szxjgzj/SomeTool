#include "BaseCalculator.h"
FBaseCalculator::FBaseCalculator(const FString& name,const FCalculatorDelegate::FDelegate& Delegate)
	:Name(name)
{
	OnRunDelegates.Add(Delegate);
	CalculThread = FRunnableThread::Create(this,*Name);
}

FBaseCalculator::FBaseCalculator()
{
	CalculThread = FRunnableThread::Create(this,*Name);
}

FBaseCalculator::~FBaseCalculator()
{
	UE_LOG(LogTemp,Warning,TEXT("CalculThread is delete"));
	if (CalculThread)
	{
		delete CalculThread;
		CalculThread = nullptr;
	}
}

bool FBaseCalculator::Init()
{
	if (!OnRunDelegates.IsEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("CalculThread is Init"));
		return true;
	}
	UE_LOG(LogTemp,Warning,TEXT("CalculThread is Not Init"));
	return false;
}

uint32 FBaseCalculator::Run()
{
	UE_LOG(LogTemp,Warning,TEXT("CalculThread is Run"));

	for (auto OnRunDelegate:OnRunDelegates)
	{
		OnRunDelegate.ExecuteIfBound();
		OnRunDelegate.Unbind();
	}
	return 0;
}

void FBaseCalculator::Stop()
{
	UE_LOG(LogTemp,Warning,TEXT("CalculThread is Stop"));
}

void FBaseCalculator::Exit()
{
	UE_LOG(LogTemp,Warning,TEXT("CalculThread is Exit"));
	if (CalculThread)
	{
		CalculThread->Kill(true);
	}
}

UBaseCalculator::UBaseCalculator()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseCalculator::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseCalculator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseCalculator::StartCalculate()
{
	new FBaseCalculator(TEXT("New Calculator"),FCalculatorDelegate::FDelegate::CreateUObject(this,&UBaseCalculator::OnCalculateWork));
}


void UBaseCalculator::OnCalculateWork_Implementation()
{
	
}

