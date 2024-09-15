// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryInstance.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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

void UGeometryInstance::GetPointsByCustomRect(
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
	if (bIsUseWorldSpace && GetStaticMesh())
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

TArray<FTransform> UGeometryInstance::GetPointsByShape(
	UShapeComponent* Shape,
	bool bIsAddInstance,
	float Distance,
	float Noise,
	bool bIsUseLookAtOrigin,
	FRotator Rotator_A,
	FRotator Rotator_B,
	bool bIsUseRandomRotation,
	FVector Size_A,
	FVector Size_B,
	bool bIsUseRandomSize,
	FRotator Rotator_Delta)
{
	TArray<FTransform> FTransforms;
	if (!Shape)
	{
		return FTransforms;
	}
	Distance = FMath::Clamp(Distance,0.f,100000.f);
	if (USphereComponent* Sphere = Cast<USphereComponent>(Shape))
		{
			float Radius = Sphere->GetScaledSphereRadius();
			FVector Origin = Sphere->GetComponentLocation();
			float SphereRound = 2.f * Radius * 3.14159f;
			int32 NumPerRound = FMath::Floor(SphereRound/Distance);
			float DeltaAnglePerRound = FMath::Clamp(360.f/ NumPerRound,0.f,360.f);

			float Longitude = 0.f;
			float Lantitude = 0.f;
			FRotator CurtRotator(0,0,0);
			while (Longitude <= 360.f)
			{
				Lantitude = 0.f;
				while (Lantitude <= 360.f)
				{
					CurtRotator.Yaw += Longitude;

					float AngleNoise = FMath::Clamp(360.f / FMath::Floor(SphereRound/Noise),0.f,360.f);
					float Lantitude_A = Lantitude + FMath::RandRange(0.f,AngleNoise);
					
					FVector Point_X = CurtRotator.Quaternion().GetForwardVector() * UKismetMathLibrary::DegCos(Lantitude_A) * Radius;
					FVector Point_Y = CurtRotator.Quaternion().GetUpVector() * UKismetMathLibrary::DegSin(Lantitude_A) * Radius;
					FVector Point = Origin + Point_X + Point_Y;
					
					FTransform InstanceTransform;
					FRotator Rotator(0,0,0);// = OriginTransform.GetRotation().Rotator();
					FVector Size(1,1,1);


					if (bIsUseLookAtOrigin)
					{
						Rotator = UKismetMathLibrary::FindLookAtRotation(Point,GetComponentLocation());
					}
					
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
					
					Rotator += Rotator_Delta;
					InstanceTransform.SetRotation(Rotator.Quaternion());
					InstanceTransform.SetScale3D(Size);
					
					FTransforms.Add(InstanceTransform);
					if (bIsAddInstance)
					{
						AddInstance(InstanceTransform,true);
					}
					
					Lantitude += DeltaAnglePerRound;
				}
				Longitude += DeltaAnglePerRound;
			}
			return FTransforms;
		}
	if (UBoxComponent* Box = Cast<UBoxComponent>(Shape))
		{
			FVector Origin = Box->GetComponentLocation();
			FVector BoxRange3D = 2 * FVector(Box->GetScaledBoxExtent().X,Box->GetScaledBoxExtent().Y,Box->GetScaledBoxExtent().Z);
			FRotator Rotator = Box->GetComponentRotation();

			int32 X = FMath::Floor(BoxRange3D.X / Distance) + 1;
			int32 Y = FMath::Floor(BoxRange3D.Y / Distance) + 1;;
			int32 Z = FMath::Floor(BoxRange3D.Z / Distance) + 1;;
			for (int32 Index_Z = 0; Index_Z < Z; ++Index_Z)
			{
				for (int32 Index_Y = 0; Index_Y < Y; ++Index_Y)
				{
					for (int32 Index_X = 0; Index_X < X; ++Index_X)
					{
						if (Index_Z > 0 && Index_Z <= Z-2 && Index_Y > 0 && Index_Y <= Y-2 && Index_X > 0 && Index_X <= Y-2)
						{
							continue;
						}

						float RandomDistanceDelta = FMath::RandRange(Noise * -1.f,Noise);
						
						FTransform InstanceTransform;
						FVector ForwardVector = Rotator.Quaternion().GetForwardVector();
						FVector RightVector = Rotator.Quaternion().GetRightVector();
						FVector UpVector = Rotator.Quaternion().GetUpVector();
						
						FVector Location = Origin
						+ Distance * Index_X * ForwardVector
						+ Distance * Index_Y * RightVector
						+ Distance * Index_Z * UpVector
						- Distance * (X - 1) * 0.5 * ForwardVector
						- Distance * (Y - 1)* 0.5 * RightVector
						- Distance * (Z - 1)* 0.5 * UpVector
						+ RandomDistanceDelta * ForwardVector
						+ RandomDistanceDelta * RightVector
						+ RandomDistanceDelta * UpVector;
						
						FRotator Rotator_A(0,0,0);
						FVector Size(1,1,1);

						if (bIsUseLookAtOrigin)
						{
							Rotator_A = UKismetMathLibrary::FindLookAtRotation(Location,Origin);
						}
						
						if (bIsUseRandomSize)
						{
							Size = FVector(
								FMath::RandRange(Size_A.X,Size_B.X),
								FMath::RandRange(Size_A.Y,Size_B.Y),
								FMath::RandRange(Size_A.Z,Size_B.Z));
						}

						if (bIsUseRandomRotation)
						{
							Rotator_A = FRotator(
								FMath::RandRange(Rotator_A.Pitch,Rotator_B.Pitch),
								FMath::RandRange(Rotator_A.Yaw,Rotator_B.Yaw),
								FMath::RandRange(Rotator_A.Roll,Rotator_B.Roll));
						}
						
						FRotator Rotator_B = FRotator(Rotator_A.Pitch + Rotator_Delta.Pitch,Rotator_A.Yaw + Rotator_Delta.Yaw,Rotator_A.Roll + Rotator_Delta.Roll);
						InstanceTransform.SetLocation(Location);
						InstanceTransform.SetRotation(Rotator_B.Quaternion());
						InstanceTransform.SetScale3D(Size);
						
						FTransforms.Add(InstanceTransform);
						if (bIsAddInstance)
						{
							AddInstance(InstanceTransform,true);
						}
					}
				}
			}
			return FTransforms;
		}
	if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Shape))
		{
			return FTransforms;
		}
	return FTransforms;
}

TArray<FTransform> UGeometryInstance::GetPointsByCircle(int32 InitCount,float InitAngle,int32 Level,float RadiusDelta)
{
	TArray<FTransform> FTransforms;
	FTransform FirstTransform;
	FirstTransform.SetLocation(GetOwner()->GetActorLocation());
	FirstTransform.SetRotation(FRotator(0,0,0).Quaternion());
	FirstTransform.SetScale3D(FVector(1,1,1));

	FTransforms.Add(FirstTransform);
	if (InitCount <= 2 || Level <= 1 || RadiusDelta <= 0.f)
	{
		return FTransforms;
	}
	float CurtAngle = InitAngle;
	float CurtRadius = 0.0f;
	int32 CurtCount = InitCount;
	for (int level = 1; level < Level; ++level)
	{
		CurtRadius = RadiusDelta*level;
		CurtCount = InitCount*level;
		for (int count = 0; count < CurtCount; ++count)
		{
			CurtAngle = InitAngle + (360.f/CurtCount) * count;
			UE_LOG(LogTemp,Warning,TEXT("CurtAngle:%f"),CurtAngle);
			//FRotator CurtRotator(0,0,0);
			//CurtRotator.Yaw = CurtAngle;
			FVector Point_X = FVector(1,0,0) * UKismetMathLibrary::DegCos(CurtAngle) * CurtRadius;
			FVector Point_Y = FVector(0,1,0) * UKismetMathLibrary::DegSin(CurtAngle) * CurtRadius;
			FVector Point = GetOwner()->GetRootComponent()->GetComponentLocation() + Point_X + Point_Y;
			//FVector Point = GetOwner()->GetActorLocation() + Point_X + Point_Y;

			FTransform CurtTransform;
			CurtTransform.SetLocation(Point);
			CurtTransform.SetRotation(FRotator(0,0,0).Quaternion());
			CurtTransform.SetScale3D(FVector(1,1,1));

			FTransforms.Add(CurtTransform);
		}
	}
	return FTransforms;
	//FTransforms.Add(FTransforms());
}
