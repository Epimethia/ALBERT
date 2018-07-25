// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/GameFramework/GameMode.h"
#include "Engine.h"
#include "PlayerShip.h"
#include "Viking_Ram_Ship.h"
#include "Viking_Shoot_Ship.h"
#include <vector>
#include <cmath>
#include "A_L_B_E_R_TGameModeBase.generated.h"


UCLASS()
class A_L_B_E_R_T_API AA_L_B_E_R_TGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void StartPlay() override;

	AA_L_B_E_R_TGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;

	std::vector<AViking_Ram_Ship*> ShipVector;
	AViking_Shoot_Ship* Ship;
	unsigned int Health;
};


