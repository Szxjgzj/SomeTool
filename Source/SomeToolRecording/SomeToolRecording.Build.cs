using UnrealBuildTool;

public class SomeToolRecording : ModuleRules
{
	public SomeToolRecording(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"RHI",
			"RenderCore",
			"Slate",
			"SlateCore",
		});

		PrivateDependencyModuleNames.Add("SignalProcessing");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"ApplicationCore",
				"AVEncoder",
				"D3D11RHI",
			});

			AddEngineThirdPartyPrivateStaticDependencies(Target, "DX11");

			PublicSystemLibraries.AddRange(new string[]
			{
				"mf.lib",
				"mfplat.lib",
				"mfreadwrite.lib",
				"mfuuid.lib",
				"d3d11.lib",
				"dxgi.lib",
			});

			PublicDelayLoadDLLs.AddRange(new string[]
			{
				"mfplat.dll",
				"mfuuid.dll",
				"Mfreadwrite.dll",
			});
		}
	}
}
