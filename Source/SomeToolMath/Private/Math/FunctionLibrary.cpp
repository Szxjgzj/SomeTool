#include "Math/FunctionLibrary.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

const FVector UFunctionLibrary::GetBezierPoint(const TArray<FVector>& Points, float Progress)
{
	TArray<FVector> RuntimePoints;
	const int32 FirstLevelNum = Points.Num();
	int32 TotalLevelNum = 0;
	int32 CurrentLevelIndex = 0;
	int32 MaxLevelIndex = FirstLevelNum - 1;
	Progress = FMath::Clamp(Progress, 0.0f, 1.0f);

	if (FirstLevelNum <= 1)
	{
		return FVector::ZeroVector;
	}

	TotalLevelNum = FirstLevelNum % 2 == 0
		? (FirstLevelNum + 1) * (FirstLevelNum / 2)
		: (FirstLevelNum + 1) * (FirstLevelNum / 2) + ((FirstLevelNum / 2) + 1);

	RuntimePoints.Init(FVector::ZeroVector, TotalLevelNum);
	for (int32 Index = 0; Index < TotalLevelNum; ++Index)
	{
		if (Index < Points.Num())
		{
			RuntimePoints[Index] = Points[Index];
			continue;
		}

		if (CurrentLevelIndex >= MaxLevelIndex)
		{
			MaxLevelIndex -= 1;
			CurrentLevelIndex = 0;
		}

		RuntimePoints[Index] = RuntimePoints[Index - MaxLevelIndex - 1]
			+ (RuntimePoints[Index - MaxLevelIndex] - RuntimePoints[Index - MaxLevelIndex - 1]) * Progress;
		CurrentLevelIndex += 1;
	}

	return RuntimePoints[TotalLevelNum - 1];
}

TArray<FTransform> UFunctionLibrary::GetPointsByShape(
	UShapeComponent* Shape,
	float Distance,
	float Noise,
	bool bIsUseLookAtOrigin,
	FRotator Rotator_A,
	FRotator Rotator_B,
	bool bIsUseRandomRotation,
	FVector Size_A,
	FVector Size_B,
	bool bIsUseRandomSize)
{
	TArray<FTransform> Transforms;
	if (!Shape)
	{
		return Transforms;
	}

	Distance = FMath::Clamp(Distance, KINDA_SMALL_NUMBER, 100000.0f);
	Noise = FMath::Max(Noise, 0.0f);

	if (USphereComponent* Sphere = Cast<USphereComponent>(Shape))
	{
		const float Radius = Sphere->GetScaledSphereRadius();
		const FVector Origin = Sphere->GetComponentLocation();
		const float SphereRound = 2.0f * Radius * 3.14159f;
		const int32 NumPerRound = FMath::Max(1, FMath::FloorToInt(SphereRound / Distance));
		const float DeltaAnglePerRound = FMath::Clamp(360.0f / NumPerRound, 0.0f, 360.0f);

		float Longitude = 0.0f;
		float Latitude = 0.0f;
		FRotator CurrentRotator(0, 0, 0);
		while (Longitude <= 360.0f)
		{
			Latitude = 0.0f;
			while (Latitude <= 360.0f)
			{
				CurrentRotator.Yaw += Longitude;

				const int32 NoiseDivisor = Noise > KINDA_SMALL_NUMBER
					? FMath::Max(1, FMath::FloorToInt(SphereRound / Noise))
					: 1;
				const float AngleNoise = Noise > KINDA_SMALL_NUMBER
					? FMath::Clamp(360.0f / NoiseDivisor, 0.0f, 360.0f)
					: 0.0f;
				const float LatitudeA = Latitude + FMath::RandRange(0.0f, AngleNoise);

				const FVector PointX = CurrentRotator.Quaternion().GetForwardVector() * UKismetMathLibrary::DegCos(LatitudeA) * Radius;
				const FVector PointY = CurrentRotator.Quaternion().GetUpVector() * UKismetMathLibrary::DegSin(LatitudeA) * Radius;
				const FVector Point = Origin + PointX + PointY;

				FTransform InstanceTransform;
				FRotator Rotator(0, 0, 0);
				FVector Size(1, 1, 1);

				if (bIsUseLookAtOrigin)
				{
					Rotator = UKismetMathLibrary::FindLookAtRotation(Point, Shape->GetComponentLocation());
				}

				if (bIsUseRandomRotation)
				{
					Rotator = FRotator(
						FMath::RandRange(Rotator_A.Pitch, Rotator_B.Pitch),
						FMath::RandRange(Rotator_A.Yaw, Rotator_B.Yaw),
						FMath::RandRange(Rotator_A.Roll, Rotator_B.Roll));
				}
				if (bIsUseRandomSize)
				{
					Size = FVector(
						FMath::RandRange(Size_A.X, Size_B.X),
						FMath::RandRange(Size_A.Y, Size_B.Y),
						FMath::RandRange(Size_A.Z, Size_B.Z));
				}

				InstanceTransform.SetLocation(Point);
				InstanceTransform.SetRotation(Rotator.Quaternion());
				InstanceTransform.SetScale3D(Size);

				Transforms.Add(InstanceTransform);

				Latitude += DeltaAnglePerRound;
			}
			Longitude += DeltaAnglePerRound;
		}
		return Transforms;
	}

	if (UBoxComponent* Box = Cast<UBoxComponent>(Shape))
	{
		const FVector Origin = Box->GetComponentLocation();
		const FVector BoxRange3D = 2 * FVector(Box->GetScaledBoxExtent().X, Box->GetScaledBoxExtent().Y, Box->GetScaledBoxExtent().Z);
		const FRotator Rotator = Box->GetComponentRotation();

		const int32 X = FMath::FloorToInt(BoxRange3D.X / Distance) + 1;
		const int32 Y = FMath::FloorToInt(BoxRange3D.Y / Distance) + 1;
		const int32 Z = FMath::FloorToInt(BoxRange3D.Z / Distance) + 1;
		for (int32 IndexZ = 0; IndexZ < Z; ++IndexZ)
		{
			for (int32 IndexY = 0; IndexY < Y; ++IndexY)
			{
				for (int32 IndexX = 0; IndexX < X; ++IndexX)
				{
					if (IndexZ > 0 && IndexZ <= Z - 2 && IndexY > 0 && IndexY <= Y - 2 && IndexX > 0 && IndexX <= X - 2)
					{
						continue;
					}

					const float RandomDistanceDelta = FMath::RandRange(Noise * -1.0f, Noise);

					FTransform InstanceTransform;
					const FVector ForwardVector = Rotator.Quaternion().GetForwardVector();
					const FVector RightVector = Rotator.Quaternion().GetRightVector();
					const FVector UpVector = Rotator.Quaternion().GetUpVector();

					const FVector Location = Origin
						+ Distance * IndexX * ForwardVector
						+ Distance * IndexY * RightVector
						+ Distance * IndexZ * UpVector
						- Distance * (X - 1) * 0.5 * ForwardVector
						- Distance * (Y - 1) * 0.5 * RightVector
						- Distance * (Z - 1) * 0.5 * UpVector
						+ RandomDistanceDelta * ForwardVector
						+ RandomDistanceDelta * RightVector
						+ RandomDistanceDelta * UpVector;

					FRotator ResultRotator(0, 0, 0);
					FVector Size(1, 1, 1);

					if (bIsUseLookAtOrigin)
					{
						ResultRotator = UKismetMathLibrary::FindLookAtRotation(Location, Origin);
					}

					if (bIsUseRandomSize)
					{
						Size = FVector(
							FMath::RandRange(Size_A.X, Size_B.X),
							FMath::RandRange(Size_A.Y, Size_B.Y),
							FMath::RandRange(Size_A.Z, Size_B.Z));
					}

					if (bIsUseRandomRotation)
					{
						ResultRotator = FRotator(
							FMath::RandRange(Rotator_A.Pitch, Rotator_B.Pitch),
							FMath::RandRange(Rotator_A.Yaw, Rotator_B.Yaw),
							FMath::RandRange(Rotator_A.Roll, Rotator_B.Roll));
					}

					const FRotator FinalRotator(ResultRotator.Pitch, ResultRotator.Yaw, ResultRotator.Roll);
					InstanceTransform.SetLocation(Location);
					InstanceTransform.SetRotation(FinalRotator.Quaternion());
					InstanceTransform.SetScale3D(Size);

					Transforms.Add(InstanceTransform);
				}
			}
		}
		return Transforms;
	}

	return Transforms;
}
