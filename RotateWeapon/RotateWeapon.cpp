#include "RotateWeapon.h"

#include "K2Node_Timeline.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SomeTool/Async/BaseAsyncAction.h"

URotateWeapon::URotateWeapon()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void URotateWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void URotateWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void URotateWeapon::OnRotate_Implementation()
{
	AddWorldRotation(FRotator(0,RotateSpeed,0));
}

void URotateWeapon::WeaponTrace_Implementation(
	float Length,
	float Radius, 
	ETraceTypeQuery TraceChannel, 
	TArray<FHitResult>& OutHits, 
	EDrawDebugTrace::Type DrawDebugType,
	FLinearColor TraceColor, 
	FLinearColor TraceHitColor, 
	float DrawTime)
{
	if (GetOwner())
	{
		for (int i = 0; i < GetInstanceCount(); i++)
		{
			TArray<AActor*> ActorsToIgnore;
			FTransform InstanceTransform;
			GetInstanceTransform(i,InstanceTransform,true);
			FVector Start = GetComponentLocation();
			FVector End = Start + (UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(Start,InstanceTransform.GetLocation())) * Length);
			UKismetSystemLibrary::SphereTraceMulti(
				GetOwner(),
				Start,
				End,
				Radius,
				TraceChannel,
				false,
				ActorsToIgnore,
				DrawDebugType,
				OutHits,
				true,
				TraceColor,
				TraceHitColor,
				DrawTime);
			if (OutHits.Num() > 0 && GetOwner() != OutHits[0].GetComponent()->GetOwner())
			{
				URotateWeapon* Target = Cast<URotateWeapon>(OutHits[0].GetComponent());
				if (Target)
				{
					BeHit(Target,i,OutHits[0].ImpactPoint,InstanceTransform.GetLocation());
					Target->BeHit(this,OutHits[0].Item,OutHits[0].ImpactPoint,InstanceTransform.GetLocation());
				}
				else
				{
					BeHit(OutHits[0].GetComponent(),OutHits[0].Item,OutHits[0].ImpactPoint,InstanceTransform.GetLocation());
				}
			}
		}
	}
}

void URotateWeapon::StartRotate(float InRate,float rotateSpeed)
{
	if (GetOwner() && GetInstanceCount() > 0)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(),EGetWorldErrorMode::ReturnNull);
		if (World)
		{
			UE_LOG(LogTemp,Log,TEXT("RotateWeapon Start"));
			RotateSpeed = rotateSpeed;
			World->GetTimerManager().SetTimer(TimerHandle,this,&URotateWeapon::OnRotate,InRate,true,-1);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("RotateWeapon Not Start"));
	}
}

void URotateWeapon::EndRotate()
{
	if (GetOwner())
	{
		UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(),EGetWorldErrorMode::ReturnNull);
		if (World)
		{
			UE_LOG(LogTemp,Log,TEXT("RotateWeapon Over"));
			World->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("RotateWeapon Not Over"));
	}
}

void URotateWeapon::BeHit_Implementation(UActorComponent* Component,const int32& Index,const FVector& HitLocation,const FVector& InstanceLocation)
{
	HitDelegate.Broadcast(Component,Index,HitLocation,InstanceLocation);
}

void URotateWeapon::AddRotateWeapon(int32 Count,float Radius,FVector Size,float YawDelta)
{
	RotateRadius = FMath::Clamp(Radius,1.0f,10000.f);;
	Count = FMath::Clamp(Count,0,99);
	int32 LastCount = GetInstanceCount();
	int32 CurtCount = LastCount + Count;
	for (int i = LastCount; i < CurtCount; i++)
	{
		float Angle = 0;//(360.f/CurtCount) * i;
		//UE_LOG(LogTemp,Warning,TEXT("Angle:%f"),Angle);
		
		FTransform InstanceTransform;
			
		FVector Location = FVector(GetComponentLocation().X + UKismetMathLibrary::DegCos(Angle)*Radius,GetComponentLocation().Y + UKismetMathLibrary::DegSin(Angle)*Radius,GetComponentLocation().Z);
		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(),Location);
		Rotator.Yaw = Rotator.Yaw + YawDelta;
			
		InstanceTransform.SetLocation(Location);
		InstanceTransform.SetRotation(Rotator.Quaternion());
		InstanceTransform.SetScale3D(Size);
		AddInstance(InstanceTransform,true);
	}

	for (int i = 0; i < CurtCount; i++)
	{
		float LastAngle;
		float CurtAngle;
		FVector CurtLocation;
		if (i < LastCount)
		{
			LastAngle = (360.f/LastCount) * i;
			CurtAngle = (360.f/CurtCount) * i;
		}
		else
		{
			LastAngle = (360.f/CurtCount) * LastCount;
			CurtAngle = (360.f/CurtCount) * i;
		}
		CurtLocation = FVector(GetComponentLocation().X + UKismetMathLibrary::DegCos(CurtAngle)*Radius,GetComponentLocation().Y + UKismetMathLibrary::DegSin(CurtAngle)*Radius,GetComponentLocation().Z);
		RotateDelegate.Broadcast(i,CurtLocation,LastAngle,CurtAngle);
	}
}

void URotateWeapon::ReduceWeapon(int32 Index)
{
	RemoveInstance(Index);
	if (GetInstanceCount() <= 0)
	{
		EndRotate();
	}
}

void URotateWeapon::UpdateInstanceLocation(int32 Index,float Radius,float Angle,FVector Size,float YawDelta)
{
	FTransform NewInstanceTransform;
	FVector NewLocation = FVector(GetComponentLocation().X + UKismetMathLibrary::DegCos(Angle)*Radius,GetComponentLocation().Y + UKismetMathLibrary::DegSin(Angle)*Radius,GetComponentLocation().Z);
	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(),NewLocation);
	NewRotator.Yaw = NewRotator.Yaw + YawDelta;
			
	NewInstanceTransform.SetLocation(NewLocation);
	NewInstanceTransform.SetRotation(NewRotator.Quaternion());
	NewInstanceTransform.SetScale3D(Size);
	
	UpdateInstanceTransform(Index,NewInstanceTransform,true,true);
}



