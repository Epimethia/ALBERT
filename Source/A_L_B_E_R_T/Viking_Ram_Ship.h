// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"

#include <cmath>

#include "Viking_Ram_Ship.generated.h"

enum STATE {
	CHILLING,
	CHASING,
	EXPLODING
};

UCLASS()
class A_L_B_E_R_T_API AViking_Ram_Ship : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViking_Ram_Ship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Ai Functions
	void Seek(FVector _Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The Model of the ship
	UStaticMeshComponent* ShipMesh;

	STATE Current_State;
	float ExplodeTimer;
	bool Exploded;

	void DestroyShip();
	//UPROPERTY(EditAnywhere) UClass* Fire;

	FVector Velocity ;
	float MaxSpeed;
	float MaxForce;
	float ApproachRadius;

	FVector Target;
};
