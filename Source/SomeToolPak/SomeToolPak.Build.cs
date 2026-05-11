using UnrealBuildTool;

public class SomeToolPak : ModuleRules
{
	public SomeToolPak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AssetRegistry",
				"Json",
				"PakFile",
				"RenderCore"
			});
	}
}
