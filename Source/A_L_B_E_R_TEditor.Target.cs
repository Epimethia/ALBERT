// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class A_L_B_E_R_TEditorTarget : TargetRules
{
	public A_L_B_E_R_TEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "A_L_B_E_R_T" } );
	}
}
