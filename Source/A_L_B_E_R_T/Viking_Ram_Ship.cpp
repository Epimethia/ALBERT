// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Ram_Ship.h"

//Function to limit vector
FVector Limit(FVector& _Vect, float _Max) {

	if (_Vect.Size() > _Max * _Max) {
		_Vect = (_Vect.GetSafeNormal()) * _Max;
	}
	return _Vect;
}

// Sets default values
AViking_Ram_Ship::AViking_Ram_Ship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ship Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Boat_Placeholder.Boat_Placeholder'")).Object);
	ShipMesh->SetSimulatePhysics(true);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	ShipMesh->SetWorldScale3D(FVector(40.0f, -40.0f, 40.0f));
	RootComponent = ShipMesh;

	WithinRange = false;

	Velocity = FVector();
	MaxSpeed = 100.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;
}

// Called when the game starts or when spawned
void AViking_Ram_Ship::BeginPlay()
{
	Super::BeginPlay();

}

//Function to seek the player
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

	////Containing the cube cats within the play area
	//if (GetActorLocation().X >= 1800.0f) {
	//	DesiredVelocity = FVector(-MaxSpeed, Velocity.Y, 0.0f);
	//}
	//else if (GetActorLocation().X <= -1800.0f) {
	//	DesiredVelocity = FVector(MaxSpeed, Velocity.Y, 0.0f);
	//}
	//else if (GetActorLocation().Y >= 1800.0f) {
	//	DesiredVelocity = FVector(Velocity.X, -MaxSpeed, 0.0f);
	//}
	//else if (GetActorLocation().Y <= -1800.0f) {
	//	DesiredVelocity = FVector(Velocity.X, MaxSpeed, 0.0f);
	//}

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
void AViking_Ram_Ship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Seek(Target);
	SetActorLocation(GetActorLocation() + Velocity);

}

