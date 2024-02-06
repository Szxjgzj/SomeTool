#include "BaseAsyncAction.h"

UBaseAsyncAction::UBaseAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

UBaseAsyncAction::~UBaseAsyncAction()
{
	UE_LOG(LogTemp,Warning,TEXT("AsyncAction is End"));
}

UBaseAsyncAction* UBaseAsyncAction::AsyncAction(UObject* worldContext,
		UCurveFloat* CurveFloat,
		float Value,
		bool bIsUseCurve,
		float A,
		float B,
		float DeltaSeconds,
		float Time,
		float FirstDelay)
{
	if (worldContext)
	{
		UBaseAsyncAction* Action = NewObject<UBaseAsyncAction>();
		Action->CurveFloat = CurveFloat;
		Action->Time = Time;
		Action->DeltaSeconds = DeltaSeconds;
		Action->CurveValue = Value;
		Action->AValue = A;
		Action->BValue = B;
		Action->bIsUseCurve = bIsUseCurve;
		Action->FirstDelay = FirstDelay;
	
		Action->WorldContext = worldContext;
		Action->RegisterWithGameInstance(worldContext);
	
		return Action;
	}
	else
	{
		return nullptr;
	}
	
}

void UBaseAsyncAction::Activate()
{
	Super::Activate();
	if (WorldContext)
	{
		World = GEngine->GetWorldFromContextObject(WorldContext,EGetWorldErrorMode::ReturnNull);
		if (World)
		{
			UE_LOG(LogTemp,Warning,TEXT("AsyncAction Start---Time:%f"),Time);
			World->GetTimerManager().SetTimer(TimerHandle,this,&UBaseAsyncAction::OnUpdate,DeltaSeconds,true,FirstDelay);
			OnStartDelegate.Broadcast(Time,CurveValue,AValue,BValue);
		}
	}
}

void UBaseAsyncAction::OnUpdate()
{
	LastTime += DeltaSeconds;
	if (LastTime > Time)
	{
		OnUpdateDelegate.Broadcast(Time,CurveValue,AValue,BValue);
		OnCompleteDelegate.Broadcast(Time,CurveValue,AValue,BValue);
		Time = 0.0f;
		if (World)
		{
			World->GetTimerManager().ClearTimer(TimerHandle);
			RemoveFromRoot();
			SetReadyToDestroy();
			GEngine->ForceGarbageCollection(true);
		}
	}
	else
	{
		if (bIsUseCurve && CurveFloat)
		{
			CurveValue = CurveFloat->GetFloatValue(LastTime);
		}
		OnUpdateDelegate.Broadcast(LastTime-DeltaSeconds,CurveValue,AValue,BValue);
	}
}
