// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enemy_Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class A_L_B_E_R_T_API AEnemy_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Projectile();
	float Lifetime;
	FVector Dir;

protected:
	UProjectileMovementComponent * ProjectileMovement;
	UStaticMeshComponent* ProjMesh;

public:	

	virtual void Tick(float DeltaTime) override;

	
};
