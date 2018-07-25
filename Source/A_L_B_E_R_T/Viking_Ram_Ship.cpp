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
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Flame_Boat/Fire_Boat.Fire_Boat'")).Object);
	ShipMesh->SetSimulatePhysics(false);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	ShipMesh->SetWorldScale3D(FVector(40.0f, -40.0f, 40.0f));
	RootComponent = ShipMesh;

	ExplodeTimer = 0.0f;
	Exploded = false;

	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/StarterContent/Blueprints/Blueprint_Effect_Fire.Blueprint_Effect_Fire'"));
	//Fire = (UClass*)ItemBlueprint.Object->GeneratedClass;
	

	Velocity = FVector();
	MaxSpeed = 4.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;
	Health = 10;
}

// Called when the game starts or when spawned
void AViking_Ram_Ship::BeginPlay()
{
	Super::BeginPlay();
	Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	Current_State = CHILLING;


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

	if (Health <= 0)
	{

	}
	//If the ship is currently chilling
	switch (Current_State) {
		case CHILLING:
			//If the player is within chasing range
			if (abs(FVector::Dist(GetActorLocation(), Target) < 1500.0f)) {
				//switch to chase
				Current_State = CHASING;
				UE_LOG(LogClass, Log, TEXT("NOW CHASING"));
				break;
			}
			//else do nothing
			break;
		case CHASING:
			//If the player moves out of chasing range
			if (abs(FVector::Dist(GetActorLocation(), Target) > 1500.0f)) {
				//Switch to chilling
				Current_State = CHILLING;
				UE_LOG(LogClass, Log, TEXT("NOW CHILLING"));

			}

			//if the player is in explode range
			else if (abs(FVector::Dist(GetActorLocation(), Target) < 200.0f)) {
				Current_State = EXPLODING;
				UE_LOG(LogClass, Log, TEXT("NOW EXPLODING"));
			}

			//Otherwise just chase
			else {
				Seek(Target);
				SetActorLocation(GetActorLocation() + Velocity);
			}
			break;
		case EXPLODING:
			if (ExplodeTimer < 250.0f) {
				
				ExplodeTimer += 100.0f * DeltaTime;
				FQuat QRotation = FQuat(FRotator(0.0f, (ExplodeTimer * ExplodeTimer) * 0.025f, 0.0f));
				SetActorRotation(QRotation, ETeleportType::None);
				//UE_LOG(LogClass, Log, TEXT("Explode Timer: %d"), ExplodeTimer);
			}
			else {
				UE_LOG(LogClass, Log, TEXT("EXPLODED"));
				Exploded = true;
			}
			break;
		default: break;
	}
	

}

void AViking_Ram_Ship::DestroyShip() {

}

