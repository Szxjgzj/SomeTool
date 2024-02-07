#include "RotateWeaponComponet.h"

#include "K2Node_Timeline.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SomeTool/Async/BaseAsyncAction.h"

URotateWeaponComponet::URotateWeaponComponet()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void URotateWeaponComponet::BeginPlay()
{
	Super::BeginPlay();
}

void URotateWeaponComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URotateWeaponComponet::OnRotate_Implementation()
{
	AddWorldRotation(FRotator(0,RotateSpeed,0));
}

void URotateWeaponComponet::WeaponTrace_Implementation(
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
				URotateWeaponComponet* Target = Cast<URotateWeaponComponet>(OutHits[0].GetComponent());
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

void URotateWeaponComponet::StartRotate(float InRate,float rotateSpeed)
{
	if (GetOwner() && Weapons.Num() > 0)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(),EGetWorldErrorMode::ReturnNull);
		if (World)
		{
			UE_LOG(LogTemp,Log,TEXT("RotateWeapon Start"));
			RotateSpeed = rotateSpeed;
			World->GetTimerManager().SetTimer(TimerHandle,this,&URotateWeaponComponet::OnRotate,InRate,true,-1);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("RotateWeapon Not Start"));
	}
}

void URotateWeaponComponet::EndRotate()
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

void URotateWeaponComponet::BeHit_Implementation(UActorComponent* Component,const int32& Index,const FVector& HitLocation,const FVector& InstanceLocation)
{
	HitDelegate.Broadcast(Component,Index,HitLocation,InstanceLocation);
}

void URotateWeaponComponet::AddRotateWeapon(int32 Count,float Radius,FVector Size,float YawDelta)
{
	RotateRadius = FMath::Clamp(Radius,1.0f,10000.f);;
	Count = FMath::Clamp(Count,0,99);
	int32 LastCount = Weapons.Num();
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
		
		UClass* WeaponClass = Cast<UClass>(WeaponsActor);
		AWeaponActor* WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass,Location,Rotator);
		Weapons.Add(WeaponActor);
		
		//AddInstance(InstanceTransform,true);
		//UpdateInstanceTransform(i,InstanceTransform,true,true);
	}

	for (int i = 0; i < CurtCount; i++)
	{
		float LastAngle;
		float CurtAngle;
		FVector CurtLocation;
		if (i < LastCount)
		{
			LastAngle = (360.f/LastCount) * i * -1;
			CurtAngle = (360.f/CurtCount) * i * -1;
		}
		else
		{
			if (LastCount == 0)
			{
				LastAngle = 0.f;
				CurtAngle = (360.f/CurtCount) * i * -1;
			}
			else
			{
				LastAngle = (360.f/LastCount) * LastCount * -1;
				CurtAngle = (360.f/CurtCount) * i * -1;
			}
		}
		CurtLocation = FVector(GetComponentLocation().X + UKismetMathLibrary::DegCos(CurtAngle)*Radius,GetComponentLocation().Y + UKismetMathLibrary::DegSin(CurtAngle)*Radius,GetComponentLocation().Z);
		RotateDelegate.Broadcast(i,CurtLocation,LastAngle,CurtAngle);
	}
}

void URotateWeaponComponet::ReduceWeapon(int32 Index)
{
	if (Weapons.Num() <= 0)
	{
		EndRotate();
	}
	else
	{
		if (Index >= 0 && Index < Weapons.Num())
		{
			FVector Location = Weapons[Index]->GetActorLocation();
			Weapons.RemoveAt(Index);
			EndDelegate.Broadcast(Index,Location,0,0);
		}
	}
}

FTransform URotateWeaponComponet::UpdateTransform(int32 Index,float Radius,float Angle,FVector Size,float YawDelta)
{
	FTransform NewInstanceTransform;
	FVector NewLocation = FVector(GetComponentLocation().X + UKismetMathLibrary::DegCos(Angle)*Radius,GetComponentLocation().Y + UKismetMathLibrary::DegSin(Angle)*Radius,GetComponentLocation().Z);
	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(),NewLocation);
	NewRotator.Yaw = NewRotator.Yaw + YawDelta;
			
	NewInstanceTransform.SetLocation(NewLocation);
	NewInstanceTransform.SetRotation(NewRotator.Quaternion());
	NewInstanceTransform.SetScale3D(Size);

	return NewInstanceTransform;
	//UpdateInstanceTransform(Index,NewInstanceTransform,true,true);
}



