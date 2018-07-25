// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerShip.h"
#include "Enemy_Camp.h"

#include "GameMode_0.generated.h"

/**
 * 
 */
UCLASS()
class A_L_B_E_R_T_API AGameMode_0 : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Constructor
	AGameMode_0();

	UWorld* World;

	AEnemy_Camp* Camp[6];
	/*AEnemy_Camp* Camp1;
	AEnemy_Camp* Camp2;
	AEnemy_Camp* Camp3;
	AEnemy_Camp* Camp4;
	AEnemy_Camp* Camp5;*/

	//Start Play Initializer
	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
