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
	ProjMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Shoot_Boat/Proj/Enemy_Proj.Enemy_Proj'")).Object);
	ProjMesh->SetupAttachment(RootComponent);
	//FQuat QRotation = FQuat(FRotator(0, 90, 0));
	//ProjMesh->SetRelativeRotation(QRotation);
	ProjMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjMesh->OnComponentHit.AddDynamic(this, &AEnemy_Projectile::OnHit);
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


void AEnemy_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogClass, Log, TEXT("HITHIT"));
	Destroy();
}
