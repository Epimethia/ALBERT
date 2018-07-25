// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Projectile.generated.h"

UCLASS()
class A_L_B_E_R_T_API AEnemy_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Projectile Mesh
	UStaticMeshComponent* ProjectileMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
