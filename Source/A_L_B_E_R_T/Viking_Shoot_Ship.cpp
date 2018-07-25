// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Shoot_Ship.h"



void AViking_Shoot_Ship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		else if (abs(FVector::Dist(GetActorLocation(), Target) < 600.0f)) {
			Current_State = ATTACK;
			UE_LOG(LogClass, Log, TEXT("NOW EXPLODING"));
		}

		//Otherwise just chase
		else {
			Seek(Target);
			SetActorLocation(GetActorLocation() + Velocity);
		}
		break;
	case ATTACK:
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
