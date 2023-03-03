using UnrealBuildTool;

public class Samurai : ModuleRules {
	public Samurai(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "NavigationSystem", "Niagara", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
