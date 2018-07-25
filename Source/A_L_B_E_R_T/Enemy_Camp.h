// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Viking_Ram_Ship.h"
#include "Viking_Shoot_Ship.h"
#include "Enemy_Camp.generated.h"

UCLASS()
class A_L_B_E_R_T_API AEnemy_Camp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Camp();
	AEnemy_Camp(float _X, float _Y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The Treasure Chest Itself
	UStaticMeshComponent* Treasure_Chest_Mesh;

	float Bobbing = 0.0f;
	
	TArray<AViking_Ship_Base*> Camp;

	FVector SpawnLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
