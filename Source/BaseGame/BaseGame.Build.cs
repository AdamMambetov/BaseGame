// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BaseGame : ModuleRules
{
	public BaseGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {});	

		PrivateIncludePaths.AddRange(new string[] {});

		PublicDependencyModuleNames.AddRange(new string[] {});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"AIModule",
			"Slate",
			"SlateCore",
			"GameplayTags",
		});
	}
}
