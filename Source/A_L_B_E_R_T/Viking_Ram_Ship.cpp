// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Ram_Ship.h"

FVector Limit(FVector& _Vect, float _Max) {

	if (_Vect.Size() > _Max * _Max) {
		_Vect = (_Vect.GetSafeNormal()) * _Max;
	}
	return _Vect;
}

// Sets default values
AViking_Ram_Ship::AViking_Ram_Ship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = { 0.0f, 0.0f, 0.0f };
	MaxSpeed = 5.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;

}

// Called when the game starts or when spawned
void AViking_Ram_Ship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AViking_Ram_Ship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Seek(Target->GetActorLocation());		//Seeking the position of the player
	//SetActorLocation(GetActorLocation() + Velocity);	//Adding the velocity to the player's location
}

// Called to bind functionality to input
void AViking_Ram_Ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AViking_Ram_Ship::Seek(FVector _Target) {
	FVector DesiredVelocity;

	//Calculated the desired velocity based on the object's position and the target position
	DesiredVelocity = _Target - GetActorLocation();

	//Calculating the distance from the object to the target via finding the length of the DesiredVelocity vect
	float Distance = DesiredVelocity.Size();

	//Normalizing
	DesiredVelocity = DesiredVelocity.GetSafeNormal() * MaxSpeed;

	//If the distance to the target is less than the approach distance (is in "approach" mode)
	if (Distance < ApproachRadius) {
		//Reduce the speed
		DesiredVelocity *= (Distance / ApproachRadius);
	}

	//Calculating the max force that would be applied to the object
	FVector Steering = DesiredVelocity - Velocity;
	Steering = Limit(Steering, MaxForce);

	//Adding the objects current Steering force to the velocity
	Velocity += Steering;

	//Limiting the velocity to max speed
	Limit(Velocity, MaxSpeed);
	Velocity.Z = 0.0f;

}

void AViking_Ram_Ship::SetTarget(APlayerShip* _TargetPlayer) {
	//Target = _TargetPlayer;
}
