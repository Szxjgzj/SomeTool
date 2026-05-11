using UnrealBuildTool;

public class SomeToolPakEditor : ModuleRules
{
	public SomeToolPakEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"SomeToolPak"
			});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AssetRegistry",
				"AssetTools",
				"DesktopPlatform",
				"Json",
				"JsonUtilities",
				"PropertyEditor",
				"Projects",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"UnrealEd"
			});
	}
}
