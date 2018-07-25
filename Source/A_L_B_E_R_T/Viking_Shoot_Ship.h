// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Viking_Ram_Ship.h"
#include "Viking_Shoot_Ship.generated.h"

/**
 * 
 */


UCLASS()
class A_L_B_E_R_T_API AViking_Shoot_Ship : public AViking_Ram_Ship
{
	GENERATED_BODY()
	
	
	virtual void Tick(float DeltaTime) override;
	
};
