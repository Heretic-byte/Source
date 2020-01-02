// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DGRG_2 : ModuleRules
{
	public DGRG_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;



        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "RHI",
            "RenderCore",
            "NavigationSystem",
            "GameplayTasks",
            "DialoguePlugin",
           "EasyActionPlugin",
           "Slate",
           "SlateCore",
            "DungeonArchitectRuntime"
        });//"UMG"


        PrivateDependencyModuleNames.AddRange(new string[] {
            "DialoguePlugin",
            "EasyActionPlugin",
           "DungeonArchitectRuntime"
            });
    }
}
