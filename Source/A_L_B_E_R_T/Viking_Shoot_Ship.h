// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <vector>
#include "Viking_Ship_Base.h"
#include "Viking_Shoot_Ship.generated.h"


UCLASS()
class A_L_B_E_R_T_API AViking_Shoot_Ship : public AViking_Ship_Base
{
	GENERATED_BODY()
	
public:

	AViking_Shoot_Ship();
	virtual void Tick(float DeltaTime) override;

	STATE Current_State;
	float AttackTimer;
	bool Exploded;



};
