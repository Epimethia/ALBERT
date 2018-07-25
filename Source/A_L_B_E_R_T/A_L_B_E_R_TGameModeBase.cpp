// Fill out your copyright notice in the Description page of Project Settings.

#include "A_L_B_E_R_TGameModeBase.h"

void AA_L_B_E_R_TGameModeBase::StartPlay() {
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(FVector(-2290.0f, 231.0f, 40.0f));
}

AA_L_B_E_R_TGameModeBase::AA_L_B_E_R_TGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

}

void AA_L_B_E_R_TGameModeBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	
	//if (!ShipVector.empty()) {
	//	for (int i = 0; i < ShipVector.size(); ++i) {
	//		//Checking if the ship is marked to explode
	//		if (ShipVector[i]->Exploded == true) {
	//			//if it is, check if the player is within range. If the player is, take damage
	//			if (abs(FVector::Dist(ShipVector[i]->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()) <= 300.0f)) {
	//				//Health -= 1;
	//				//UE_LOG(LogClass, Log, TEXT("HEALTH: %d"), Health);
	//			}
	//			ShipVector[i]->Destroy();
	//			GEngine->ForceGarbageCollection(true);
	//			ShipVector.erase(ShipVector.begin() + i);
	//		}
	//		//Otherwise update the target location
	//		else {
	//			ShipVector[i]->Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//		}

	//		
	//	}
	//}

	

}