// Fill out your copyright notice in the Description page of Project Settings.
#include "FunctionLibrary.h"

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