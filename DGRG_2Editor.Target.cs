// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DGRG_2EditorTarget : TargetRules
{
	public DGRG_2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("DGRG_2");// "AssetTools",
        ExtraModuleNames.Add("DGRG_Automation");
    }
}
