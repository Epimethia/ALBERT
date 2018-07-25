// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Ship_Base.h"


FVector AViking_Ship_Base::Limit(FVector& _Vect, float _Max) {

	if (_Vect.Size() > _Max * _Max) {
		_Vect = (_Vect.GetSafeNormal()) * _Max;
	}
	return _Vect;
}


// Sets default values
AViking_Ship_Base::AViking_Ship_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AViking_Ship_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AViking_Ship_Base::Seek(FVector _Target) {
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

// Called every frame
void AViking_Ship_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

