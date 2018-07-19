// Fill out your copyright notice in the Description page of Project Settings.

#include "Viking_Ram_Ship.h"


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
}

// Called when the game starts or when spawned
void AViking_Ram_Ship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AViking_Ram_Ship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

