using UnrealBuildTool;

public class SomeToolMath : ModuleRules
{
	public SomeToolMath(ReadOnlyTargetRules Target) : base(Target)
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
