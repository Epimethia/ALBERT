// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



#include "Viking_Ship_Base.h"

#include "Viking_Ram_Ship.generated.h"

UCLASS()
class A_L_B_E_R_T_API AViking_Ram_Ship : public AViking_Ship_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViking_Ram_Ship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Exploded;
};
