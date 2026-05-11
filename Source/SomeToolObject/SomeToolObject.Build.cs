using UnrealBuildTool;

public class SomeToolObject : ModuleRules
{
	public SomeToolObject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			});
	}
}
