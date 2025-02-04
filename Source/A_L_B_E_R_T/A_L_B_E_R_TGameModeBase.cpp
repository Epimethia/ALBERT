// Fill out your copyright notice in the Description page of Project Settings.

#include "A_L_B_E_R_TGameModeBase.h"

void AA_L_B_E_R_TGameModeBase::StartPlay() {

	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(FVector(-2290.0f, 231.0f, 40.0f));

	//Generating ships
	

	Health = 10;

	for (int i = 0; i < 10; ++i) {
		AViking_Ram_Ship* Ship = GetWorld()->SpawnActor<AViking_Ram_Ship>(AViking_Ram_Ship::StaticClass(), FVector(0.0f, 0.0f, 40.0f), FRotator(0.0f, 0.0f, 0.0f));
		ShipVector.push_back(Ship);
	}
	AViking_Shoot_Ship* Ship = GetWorld()->SpawnActor<AViking_Shoot_Ship>(AViking_Shoot_Ship::StaticClass(), FVector(-1000.0f, 0.0f, 40.0f), FRotator(0.0f, 0.0f, 0.0f));
	ShipVector.push_back(Ship);
}

AA_L_B_E_R_TGameModeBase::AA_L_B_E_R_TGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APlayerShip::StaticClass();

}

void AA_L_B_E_R_TGameModeBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	
	if (!ShipVector.empty()) {
		for (int i = 0; i < ShipVector.size(); ++i) {
			if (!ShipVector[i]) {
				ShipVector.erase(ShipVector.begin() + i);
			}
			else {
				ShipVector[i]->Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			}
		}

	}


	

}