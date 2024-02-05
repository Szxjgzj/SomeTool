// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryInstance.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

UGeometryInstance::UGeometryInstance()
{
}

void UGeometryInstance::BeginPlay()
{
	Super::BeginPlay();
}

void UGeometryInstance::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGeometryInstance::AddCudeInstanceByCounts(
	FTransform OriginTransform,
	FVector Counts3D,
	FVector Distance3D,
	bool bIsUseWorldSpace,
	FRotator Rotator_A,
	FRotator Rotator_B,
	bool bIsUseRandomRotation,
	FVector Size_A,
	FVector Size_B,
	bool bIsUseRandomSize)
{
	if (bIsUseWorldSpace)
	{
		for (int Index_Z = 0; Index_Z < Counts3D.Z; ++Index_Z)
		{
			for (int Index_Y = 0; Index_Y < Counts3D.Y; ++Index_Y)
			{
				for (int Index_X = 0; Index_X < Counts3D.X; ++Index_X)
				{
					FTransform InstanceTransform;
					
					FVector ForwardVector = OriginTransform.GetRotation().GetForwardVector();
					FVector RightVector = OriginTransform.GetRotation().GetRightVector();
					FVector UpVector = OriginTransform.GetRotation().GetUpVector();
					
					FVector Location = OriginTransform.GetLocation()
					+ Distance3D.X * Index_X * ForwardVector
					+ Distance3D.Y * Index_Y * RightVector
					+ Distance3D.Z * Index_Z * UpVector
					- Distance3D.X * (Counts3D.X - 1) * 0.5 * ForwardVector
					- Distance3D.Y * (Counts3D.Y - 1)* 0.5 * RightVector
					- Distance3D.Z * (Counts3D.Z - 1)* 0.5 * UpVector;
					
					UE_LOG(LogTemp,Warning,TEXT("Location:%f,%f,%f"),Location.X,Location.Y,Location.Z);
					
					FRotator Rotator;// = OriginTransform.GetRotation().Rotator();
					FVector Size = OriginTransform.GetScale3D();
					if (bIsUseRandomRotation)
					{
						Rotator = FRotator(
							FMath::RandRange(Rotator_A.Pitch,Rotator_B.Pitch),
							FMath::RandRange(Rotator_A.Yaw,Rotator_B.Yaw),
							FMath::RandRange(Rotator_A.Roll,Rotator_B.Roll));
					}
					if (bIsUseRandomSize)
					{
						Size = FVector(
							FMath::RandRange(Size_A.X,Size_B.X),
							FMath::RandRange(Size_A.Y,Size_B.Y),
							FMath::RandRange(Size_A.Z,Size_B.Z));
					}
					
					InstanceTransform.SetLocation(Location);
					InstanceTransform.SetRotation(Rotator.Quaternion());
					InstanceTransform.SetScale3D(Size);
					
					AddInstance(InstanceTransform,bIsUseWorldSpace);
				}
			}
		}
	}
}

void UGeometryInstance::AddCudeInstanceByRange(
	UShapeComponent* Shape,
	float Distance,
	float Noise,
	bool bIsUseWorldSpace,
	FRotator Rotator_A,
	FRotator Rotator_B,
	bool bIsUseRandomRotation,
	FVector Size_A,
	FVector Size_B,
	bool bIsUseRandomSize)
{
	if (!bIsUseWorldSpace)
	{
		return;
	}
	Distance = FMath::Clamp(Distance,0,100000.f);
	if (Shape)
	{
		if (USphereComponent* Sphere = Cast<USphereComponent>(Shape))
		{
			
			float Radius = Sphere->GetScaledSphereRadius();
			FVector Origin = Sphere->GetComponentLocation();
			float SphereRound = 2.f * Radius * 3.14159f;
			int32 NumPerRound = FMath::Floor(SphereRound/Distance);
			float DeltaAnglePerRound = FMath::Clamp(360.f/ NumPerRound,0,360.f);

			float Longitude = 0.f;
			float Lantitude = 0.f;
			FRotator CurtRotator(0,0,0);
			while (Longitude <= 360.f)
			{
				Lantitude = 0.f;
				while (Lantitude <= 360.f)
				{
					CurtRotator.Yaw += Longitude;

					float AngleNoise = FMath::Clamp(360.f / FMath::Floor(SphereRound/Noise),0,360.f);
					float Lantitude_A = Lantitude + FMath::RandRange(0.f,AngleNoise);
					
					FVector Point_X = CurtRotator.Quaternion().GetForwardVector() * UKismetMathLibrary::DegCos(Lantitude_A)*Radius;
					FVector Point_Y = CurtRotator.Quaternion().GetUpVector() * UKismetMathLibrary::DegSin(Lantitude_A) * Radius;
					FVector Point = Origin + Point_X + Point_Y;
					
					FTransform InstanceTransform;
					FRotator Rotator(0,0,0);// = OriginTransform.GetRotation().Rotator();
					FVector Size(1,1,1);
					
					if (bIsUseRandomRotation)
					{
						Rotator = FRotator(
							FMath::RandRange(Rotator_A.Pitch,Rotator_B.Pitch),
							FMath::RandRange(Rotator_A.Yaw,Rotator_B.Yaw),
							FMath::RandRange(Rotator_A.Roll,Rotator_B.Roll));
					}
					if (bIsUseRandomSize)
					{
						Size = FVector(
							FMath::RandRange(Size_A.X,Size_B.X),
							FMath::RandRange(Size_A.Y,Size_B.Y),
							FMath::RandRange(Size_A.Z,Size_B.Z));
					}
					
					InstanceTransform.SetLocation(Point);
					InstanceTransform.SetRotation(Rotator.Quaternion());
					InstanceTransform.SetScale3D(Size);
					AddInstance(InstanceTransform,true);
					
					
					Lantitude += DeltaAnglePerRound;
				}
				Longitude += DeltaAnglePerRound;
			}
			return;
		}
		if (UBoxComponent* Box = Cast<UBoxComponent>(Shape))
		{
			return;
		}
		if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Shape))
		{
			return;
		}
	}
}
