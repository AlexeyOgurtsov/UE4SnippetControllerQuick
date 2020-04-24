// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjControllerQuickEditorTarget : TargetRules
{
	public ProjControllerQuickEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "ProjControllerQuick" } );

		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
