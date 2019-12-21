// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DGRG_2Target : TargetRules
{
	public DGRG_2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("DGRG_2");
        //ExtraModuleNames.Add("DGRG_Automation");

    }
}
