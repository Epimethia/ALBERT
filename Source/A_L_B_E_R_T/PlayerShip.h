// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include <cmath>

#include "PlayerShip.generated.h"

UCLASS()
class A_L_B_E_R_T_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	int Health;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector GunOffset;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;
	FVector Velocity;
	FVector Acceleration;
	float FireRate;
	float MaxSpeed;
	float MaxForce;
	float ApproachRadius;
	bool bCanFire;
	bool bFiring;
	//The static mesh for the Ship. Make it editable for now
	UStaticMeshComponent* ShipMesh;
	UStaticMeshComponent* Ship_Rudder_Mesh;
	UStaticMeshComponent* Viking_Steer;
	UStaticMeshComponent* Viking_Throw;

	class UCameraComponent* Camera;
	class USpringArmComponent* Camera_Springarm;


	float MoveSpeed;
	void Movement(float DeltaSeconds);
	void FireShot(FVector FireDirection);
	void FiringShot();
	void StopingFire();
	void ShotTimerExpired();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;
	static const FName FireMouseBinding;

private:

	//Turning Variables
	float fFacingDegree;
	float fCurrentTurnRate;
	float fMaxTurnRate;

	//Speed Variables
	float fMaxSpeed;
	float fMaxBackSpeed;
	float fCurrentSpeed;
	float ForwardValue;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;
	class APlayerController* MyController;


};
