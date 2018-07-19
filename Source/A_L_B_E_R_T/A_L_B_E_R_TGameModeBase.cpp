// Fill out your copyright notice in the Description page of Project Settings.

#include "A_L_B_E_R_TGameModeBase.h"

AA_L_B_E_R_TGameModeBase::AA_L_B_E_R_TGameModeBase() {
	// set default pawn class to our character class
	DefaultPawnClass = APlayerShip::StaticClass();

	FActorSpawnParameters SpawnInfo;
	//Ship1 = GetWorld()->SpawnActor<AViking_Ram_Ship>(AViking_Ram_Ship::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
}