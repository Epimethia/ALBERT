// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_0.h"


AGameMode_0::AGameMode_0() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

}

void AGameMode_0::StartPlay() {
	Super::StartPlay();

	World = GetWorld();
	FRotator Rot(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Camp[0] = World->SpawnActor<AEnemy_Camp>(FVector(18850.0f, 850.0f, 80.0f), Rot, params);
	Camp[1] = World->SpawnActor<AEnemy_Camp>(FVector(4370.0, -20200.0, 80.0f), Rot, params);
	Camp[2] = World->SpawnActor<AEnemy_Camp>(FVector(0.0f, -2440.0f, 80.0f), Rot, params);
	Camp[3] = World->SpawnActor<AEnemy_Camp>(FVector(-5920.0, 20270.0, 80.0f), Rot, params);
	Camp[4] = World->SpawnActor<AEnemy_Camp>(FVector(-22170.0, 23610.0, 80.0f), Rot, params);
	Camp[5] = World->SpawnActor<AEnemy_Camp>(FVector(-28710.0, 3920.0, 80.0f), Rot, params);

}

void AGameMode_0::Tick(float DeltaSeconds) {

}
