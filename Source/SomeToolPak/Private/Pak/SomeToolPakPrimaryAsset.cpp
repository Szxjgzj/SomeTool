#include "Pak/SomeToolPakPrimaryAsset.h"

const FPrimaryAssetType USomeToolPakPrimaryAsset::PrimaryAssetType = TEXT("SomeToolPak");

FPrimaryAssetId USomeToolPakPrimaryAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(PrimaryAssetType, GetFName());
}
