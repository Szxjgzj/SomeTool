using UnrealBuildTool;

public class SomeToolAsyncTask : ModuleRules
{
	public SomeToolAsyncTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			});
	}
}
