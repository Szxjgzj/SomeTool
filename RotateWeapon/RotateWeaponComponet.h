#pragma once
#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RotateWeaponComponet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHitDelegate,UActorComponent*,ActorComp,int32,Index,FVector,HitLocation,FVector,InstanceLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRotateDelegate,int32,Index,FVector,CurtLocation,float,LastAngle,float,CurtAngle);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOMETOOL_API URotateWeaponComponet : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	URotateWeaponComponet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnRotate();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void WeaponTrace(
		float Length,
		float Radius,
		ETraceTypeQuery TraceChannel,
		TArray<FHitResult>& OutHits,
		EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForOneFrame,
		FLinearColor TraceColor = FLinearColor::Red,
		FLinearColor TraceHitColor = FLinearColor::Green,
		float DrawTime = 5.f
	);
	
	UFUNCTION(BlueprintCallable)
	void StartRotate(float InRate = 0.0166f,float rotateSpeed = 5.0f);

	UFUNCTION(BlueprintCallable)
	void EndRotate();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void BeHit(UActorComponent* Component,const int32& Index,const FVector& HitLocation = FVector(0,0,0),const FVector& InstanceLocation = FVector(0,0,0));
	
	UFUNCTION(BlueprintCallable)
	void AddRotateWeapon(AWeaponActor* Weapon,int32 Count, float Radius,FVector Size = FVector(1,1,1),float YawDelta = 0);

	UFUNCTION(BlueprintCallable)
	void ReduceWeapon(int32 Index);

	UFUNCTION(BlueprintCallable)
	FTransform UpdateTransform(int32 Index,float Radius = 500.f,float Angle = 0.f,FVector Size = FVector(1,1,1),float YawDelta = 0.f);
	
	UPROPERTY(BlueprintAssignable,Category ="Weapon Hit Events",DisplayName="On Weapon Hit")
	FOnHitDelegate HitDelegate;
	
	UPROPERTY(BlueprintAssignable,Category ="Weapon Start Events",DisplayName="On Weapon Add")
	FOnRotateDelegate RotateDelegate;

	UPROPERTY(BlueprintAssignable,Category ="Weapon Start Events",DisplayName="On Weapon End")
	FOnRotateDelegate EndDelegate;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AWeaponActor*> Weapons;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeaponActor> WeaponsActor;

private:
	FTimerHandle TimerHandle;
	float RotateSpeed = 1.f;
	float RotateRadius = 100.f;
};
