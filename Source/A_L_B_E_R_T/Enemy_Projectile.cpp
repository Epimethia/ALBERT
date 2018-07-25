// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Projectile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
AEnemy_Projectile::AEnemy_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjMesh"));
	ProjMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Shoot_Boat/Enemy_Proj.Enemy_Proj'")).Object);
	ProjMesh->SetSimulatePhysics(false);
	ProjMesh->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));
	ProjMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ProjMesh;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjMesh;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	Lifetime = 0.0f;
	Dir = FVector();
	InitialLifeSpan = 3.0f;

}

void AEnemy_Projectile::Tick(float DeltaTime) {
	Lifetime += 300.0f * DeltaTime;
}
