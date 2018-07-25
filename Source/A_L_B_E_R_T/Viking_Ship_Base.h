// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include <cmath>
#include "Viking_Ship_Base.generated.h"


enum STATE {
	CHILLING,
	CHASING,
	ATTACK
};

UCLASS()
class A_L_B_E_R_T_API AViking_Ship_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViking_Ship_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Ai Functions
	void Seek(FVector _Target);
	FVector Limit(FVector& _Vect, float _Max);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The Model of the ship
	UStaticMeshComponent* ShipMesh;

	STATE Current_State;

	float AttackTimer;
	int Health;

	FVector Velocity;
	float MaxSpeed;
	float MaxForce;
	float ApproachRadius;

	FVector Target;
};
