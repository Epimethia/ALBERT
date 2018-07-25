// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Shoot_Ship.h"

AViking_Shoot_Ship::AViking_Shoot_Ship() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ship Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Shoot_Boat/Viking_Shoot_Ship.Viking_Shoot_Ship'")).Object);
	ShipMesh->SetSimulatePhysics(false);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	
	Current_State = CHILLING;

	AttackTimer = 0.0f;
	Exploded = false;

	Tags.Add(FName("Enemy"));

	Velocity = FVector();
	MaxSpeed = 5.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;
	Health = 10;
}

void AViking_Shoot_Ship::Tick(float DeltaTime)
{
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
		break;
	case CHASING:
		//If the player moves out of chasing range
		if (abs(FVector::Dist(GetActorLocation(), Target) > 1500.0f)) {
			//Switch to chilling
			Current_State = CHILLING;
			UE_LOG(LogClass, Log, TEXT("NOW CHILLING"));

		}

		//if the player is in explode range
		else if (abs(FVector::Dist(GetActorLocation(), Target) < 800.0f)) {
			Current_State = ATTACK;
			UE_LOG(LogClass, Log, TEXT("NOW SHOOTING"));
		}
		else if (abs(FVector::Dist(GetActorLocation(), Target) > 1500.0f))
		{
			Current_State = CHASING;
		}

		//Otherwise just chase
		else {
			Seek(Target);
			SetActorLocation(GetActorLocation() + Velocity);
			SetActorRotation(Velocity.Rotation() + FRotator(0.0f, 90.0f, 0.0f));
		}
		break;
	case ATTACK:
		if (abs(FVector::Dist(GetActorLocation(), Target) > 800.0f))
		{
			Current_State = CHASING;
		}
		if (AttackTimer >= 250.0f) {
			UE_LOG(LogTemp, Warning, TEXT("EnemyShot"));
			FVector FireDirec = GetActorLocation() - Target + FVector(0.0f, 0.0f, 20.0f);
			FireDirec = FireDirec.RotateAngleAxis(180, FVector(0, 0, 1));
			if (FireDirec.SizeSquared() > 0.0f)
			{
				const FRotator FireRotation = FireDirec.Rotation();
				FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(FVector(240.0f, 0.0f, 0.0f)) + FVector(0.0f, 0.0f, 20.0f);
				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					// spawn the projectile
					World->SpawnActor<AEnemy_Projectile>(SpawnLocation, FireRotation);
				}
				AttackTimer = 0.0f;
			}
		}
		else {
			AttackTimer += 300.0f * DeltaTime;
		}
		break;
	default: break;
	}
}



