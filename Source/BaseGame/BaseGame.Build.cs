// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BaseGame : ModuleRules
{
	public BaseGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"BaseGame/Private/",
		});	
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",	 
			"AIModule",
			"DeveloperSettings",
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"GameplayTags",
		});		
		
		DynamicallyLoadedModuleNames.AddRange(new string[] {});
	}
}
