// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Viking_Ram_Ship.h"
#include "Enemy_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <vector>

#include "Viking_Shoot_Ship.generated.h"

/**
 * 
 */
UCLASS()
class A_L_B_E_R_T_API AViking_Shoot_Ship : public AViking_Ram_Ship
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	//Vector of Bullets
	std::vector<AEnemy_Projectile*> EnemyBullets;
};
