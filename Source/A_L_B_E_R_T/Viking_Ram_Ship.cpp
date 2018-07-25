// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Ram_Ship.h"
//Function to limit vector

// Sets default values
AViking_Ram_Ship::AViking_Ram_Ship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ship Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Flame_Boat/Viking_Ram_Ship.Viking_Ram_Ship'")).Object);
	ShipMesh->SetSimulatePhysics(false);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	RootComponent = ShipMesh;

	AttackTimer = 0.0f;
	Exploded = false;

	Current_State = CHILLING;
	Tags.Add(FName("Enemy"));

	Velocity = FVector();
	MaxSpeed = 5.0f;
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

// Called every frame
void AViking_Ram_Ship::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (Exploded) Destroy();

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
				Current_State = ATTACK;
				UE_LOG(LogClass, Log, TEXT("NOW EXPLODING"));
			}

			//Otherwise just chase
			else {
				Seek(Target);
				SetActorLocation(GetActorLocation() + Velocity);
				SetActorRotation(Velocity.Rotation() + FRotator(0.0f, 90.0f, 0.0f));
			}
			break;
		case ATTACK:
			if (AttackTimer < 150.0f) {
				
				AttackTimer += 300.0f * DeltaTime;
				FQuat QRotation = FQuat(FRotator(0.0f, (AttackTimer * AttackTimer) * 0.04f, 0.0f));
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


