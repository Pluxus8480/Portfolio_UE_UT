// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Proj_UnTe : ModuleRules
{
	public Proj_UnTe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "Proj_UnTe" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "PaperZD" });
    }
}
