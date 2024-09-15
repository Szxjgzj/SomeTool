// Fill out your copyright notice in the Description page of Project Settings.
#include "FunctionLibrary.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

const FVector UFunctionLibrary::GetBezierPoint(const TArray<FVector>& points, float progress)
{
	TArray<FVector> Points;
	int32 FirstLevel_Num = points.Num();
	int32 TotalLevel_Num = 0;
	int32 CurtLevel_Index = 0;
	int32 MaxLevel_Index = FirstLevel_Num-1;
	progress = FMath::Clamp(progress,0.0f,1.0f);
	if (FirstLevel_Num > 1)
	{
		TotalLevel_Num = FirstLevel_Num%2 == 0?(FirstLevel_Num + 1)*(FirstLevel_Num/2):(FirstLevel_Num + 1)*(FirstLevel_Num/2) + ((FirstLevel_Num/2)+1);
		for (int i=0;i<TotalLevel_Num;++i)
		{
			Points.Add(FVector(0,0,0));
		}
		for (int i=0;i<TotalLevel_Num;++i)
		{
			if (i<points.Num())
			{
				Points[i] = points[i];
			}
			else
			{
				if (CurtLevel_Index >= MaxLevel_Index)
				{
					MaxLevel_Index -= 1;
					CurtLevel_Index = 0;
				}
				Points[i] = Points[i-MaxLevel_Index-1] + (Points[i-MaxLevel_Index]-Points[i-MaxLevel_Index-1])*progress;
				CurtLevel_Index += 1;
			}
		}
		return Points[TotalLevel_Num-1];
	}
	else
	{
		return FVector(0,0,0);
	}
}

TArray<FTransform> UFunctionLibrary::GetPointsByShape(UShapeComponent* Shape, float Distance,
	float Noise, bool bIsUseLookAtOrigin, FRotator Rotator_A, FRotator Rotator_B, bool bIsUseRandomRotation,
	FVector Size_A, FVector Size_B, bool bIsUseRandomSize)
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
						Rotator = UKismetMathLibrary::FindLookAtRotation(Point,Shape->GetComponentLocation());
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
					
					InstanceTransform.SetRotation(Rotator.Quaternion());
					InstanceTransform.SetScale3D(Size);
					
					FTransforms.Add(InstanceTransform);
					
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
						
						FRotator Rotator_B = FRotator(Rotator_A.Pitch,Rotator_A.Yaw,Rotator_A.Roll);
						InstanceTransform.SetLocation(Location);
						InstanceTransform.SetRotation(Rotator_B.Quaternion());
						InstanceTransform.SetScale3D(Size);
						
						FTransforms.Add(InstanceTransform);
					}
				}
			}
			return FTransforms;
		}
	return FTransforms;
}
