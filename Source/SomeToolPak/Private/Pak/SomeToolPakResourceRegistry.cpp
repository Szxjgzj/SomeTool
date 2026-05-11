#include "Pak/SomeToolPakResourceRegistry.h"

#if WITH_EDITOR
#include "UObject/ObjectSaveContext.h"

namespace
{
FName MakeRegistryNamespace(const UObject& Registry)
{
	UPackage* Package = Registry.GetOutermost();
	if (!Package)
	{
		return NAME_None;
	}

	FString Name = Package->GetName();
	Name.ReplaceInline(TEXT("/"), TEXT("."));
	while (Name.StartsWith(TEXT(".")))
	{
		Name.RightChopInline(1);
	}
	return Name.IsEmpty() ? NAME_None : FName(*Name);
}

FName MakeResourceKey(const FSoftObjectPath& Path)
{
	FString Key = Path.GetAssetName();
	if (Key.EndsWith(TEXT("_C")))
	{
		Key.LeftChopInline(2);
	}
	return Key.IsEmpty() ? NAME_None : FName(*Key);
}

FName MakeUniqueKey(const FName BaseKey, const TSet<FName>& UsedKeys)
{
	if (BaseKey.IsNone() || !UsedKeys.Contains(BaseKey))
	{
		return BaseKey;
	}

	const FString BaseName = BaseKey.ToString();
	int32 Suffix = 1;
	FName Candidate;
	do
	{
		Candidate = FName(*FString::Printf(TEXT("%s_%d"), *BaseName, Suffix++));
	}
	while (UsedKeys.Contains(Candidate));

	return Candidate;
}

template <typename ObjectMapType, typename ClassMapType>
void FixGeneratedKeys(
	ObjectMapType& ObjectResources,
	ClassMapType& ClassResources,
	bool& bOutChanged)
{
	bool bMapChanged = false;
	TSet<FName> UsedKeys;

	TMap<FName, TSoftObjectPtr<UObject>> FixedObjects;
	for (const TPair<FName, TSoftObjectPtr<UObject>>& Entry : ObjectResources)
	{
		FName Key = Entry.Key;
		if (!Entry.Value.IsNull())
		{
			Key = MakeUniqueKey(MakeResourceKey(Entry.Value.ToSoftObjectPath()), UsedKeys);
			bMapChanged |= Key != Entry.Key;
		}

		if (!Key.IsNone() && !FixedObjects.Contains(Key))
		{
			FixedObjects.Add(Key, Entry.Value);
			UsedKeys.Add(Key);
		}
	}

	TMap<FName, TSoftClassPtr<UObject>> FixedClasses;
	for (const TPair<FName, TSoftClassPtr<UObject>>& Entry : ClassResources)
	{
		FName Key = Entry.Key;
		if (!Entry.Value.IsNull())
		{
			Key = MakeUniqueKey(MakeResourceKey(Entry.Value.ToSoftObjectPath()), UsedKeys);
			bMapChanged |= Key != Entry.Key;
		}

		if (!Key.IsNone() && !FixedClasses.Contains(Key))
		{
			FixedClasses.Add(Key, Entry.Value);
			UsedKeys.Add(Key);
		}
	}

	if (bMapChanged)
	{
		ObjectResources = MoveTemp(FixedObjects);
		ClassResources = MoveTemp(FixedClasses);
		bOutChanged = true;
	}
}
}

bool USomeToolPakResourceRegistry::SynchronizeGeneratedFields()
{
	bool bChanged = false;
	const FName GeneratedNamespace = MakeRegistryNamespace(*this);
	if (!GeneratedNamespace.IsNone() && Namespace != GeneratedNamespace)
	{
		Namespace = GeneratedNamespace;
		bChanged = true;
	}

	FixGeneratedKeys(SoftObjects, SoftClasses, bChanged);

	return bChanged;
}

void USomeToolPakResourceRegistry::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (SynchronizeGeneratedFields())
	{
		Modify();
		MarkPackageDirty();
	}
}

void USomeToolPakResourceRegistry::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	SynchronizeGeneratedFields();
}

void USomeToolPakResourceRegistry::PostRename(UObject* OldOuter, const FName OldName)
{
	Super::PostRename(OldOuter, OldName);
	if (SynchronizeGeneratedFields())
	{
		MarkPackageDirty();
	}
}
#endif
