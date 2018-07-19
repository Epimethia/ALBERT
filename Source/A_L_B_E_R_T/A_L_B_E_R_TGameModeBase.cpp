// Fill out your copyright notice in the Description page of Project Settings.

#include "A_L_B_E_R_TGameModeBase.h"

void AA_L_B_E_R_TGameModeBase::StartPlay() {
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}

AA_L_B_E_R_TGameModeBase::AA_L_B_E_R_TGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (GetWorld() == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("World pointer is null"));
		return;
	}
	
	//The player pawn class
	DefaultPawnClass = APlayerShip::StaticClass();

	//Generating ships
	for (int i = 0; i < 10; ++i) {
		AViking_Ram_Ship* Ship = GetWorld()->SpawnActor<AViking_Ram_Ship>(AViking_Ram_Ship::StaticClass(), FVector(200.0f * i, 200.0f * i, 300.0f), FRotator(0.0f, 0.0f, 0.0f));
		ShipVector.push_back(Ship);
	}

}

void AA_L_B_E_R_TGameModeBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	for (const auto it : ShipVector) {
		it->Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	}
}