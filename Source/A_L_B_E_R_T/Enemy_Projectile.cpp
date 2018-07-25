// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Projectile.h"


// Sets default values
AEnemy_Projectile::AEnemy_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ship Mesh
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Flame_Boat/Fire_Boat.Fire_Boat'")).Object);
	ProjectileMesh->SetSimulatePhysics(false);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ProjectileMesh;

}

// Called when the game starts or when spawned
void AEnemy_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

