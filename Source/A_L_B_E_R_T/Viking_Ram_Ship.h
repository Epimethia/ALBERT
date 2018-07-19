// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//Model Components
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "PlayerShip.h"

#include "Viking_Ram_Ship.generated.h"

UCLASS()
class A_L_B_E_R_T_API AViking_Ram_Ship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AViking_Ram_Ship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Velocity;
	FVector Acceleration;
	float MaxSpeed;
	float MaxForce;
	float ApproachRadius;
	APlayerShip* Target;

	UMeshComponent* ShipMesh;

	void Seek(FVector _Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetTarget(APlayerShip* _TargetPlayer);
	
};
