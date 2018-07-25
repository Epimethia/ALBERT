// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Shoot_Ship.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/Engine.h"
#include <iostream>
#include <string>

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
		else {
			
			// Spawn projectile at an offset from this pawn
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
		else if (abs(FVector::Dist(GetActorLocation(), Target) < 4000.0f)) {
			Current_State = ATTACK;
			UE_LOG(LogClass, Log, TEXT("NOW SHOOTING"));
		}
		else if (abs(FVector::Dist(GetActorLocation(), Target) > 4000.0f))
		{
			Current_State = CHASING;
		}

		//Otherwise just chase
		else {
			Seek(Target);
			SetActorLocation(GetActorLocation() + Velocity);
			SetActorRotation(Velocity.Rotation());
		}
		break;
	case ATTACK:
		if (abs(FVector::Dist(GetActorLocation(), Target) > 4000.0f))
		{
			Current_State = CHASING;
		}
		if (AttackTimer >= 250.0f) {
			UE_LOG(LogTemp, Warning, TEXT("EnemyShot"));
			//AEnemy_Projectile* Proj = GetWorld()->SpawnActor<AEnemy_Projectile>(AEnemy_Projectile::StaticClass());
			//Proj->Dir = GetActorLocation() - Target;
			//EnemyBullets.push_back(Proj);
			FVector FireDirec = GetActorLocation() - Target + FVector(0.0f, 0.0f, 20.0f);
			FireDirec = FireDirec.RotateAngleAxis(180, FVector(0, 0, 1));
			if (FireDirec.SizeSquared() > 0.0f)
			{
				const FRotator FireRotation = FireDirec.Rotation();
				FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(FVector(170.0f, 0.0f, 0.0f)) + FVector(0.0f, 0.0f, 20.0f);
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


