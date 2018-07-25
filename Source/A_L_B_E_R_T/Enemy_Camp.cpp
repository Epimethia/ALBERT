// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Camp.h"

// Sets default values
AEnemy_Camp::AEnemy_Camp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Treasure_Chest_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Camp"));
	RootComponent = Treasure_Chest_Mesh;
	Treasure_Chest_Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Treasure_Chest/Chest_Merged.Chest_Merged'")).Object);
	Treasure_Chest_Mesh->SetRelativeTransform(FTransform(FRotator(10.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, -50.0f), FVector(4.0f, 4.0f, 4.0f)));
	Treasure_Chest_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Treasure_Chest_Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Treasure_Chest_Mesh->OnComponentHit.AddDynamic(this, &AEnemy_Camp::OnHit);

}

AEnemy_Camp::AEnemy_Camp(float _X, float _Y)
{
	
	AEnemy_Camp();
	

}

// Called when the game starts or when spawned
void AEnemy_Camp::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
	UWorld* World = GetWorld();

	for (int i = 0; i < 4; ++i) {
		AViking_Ship_Base* s;

		float Theta = FMath::FRandRange(0.0f, 8.0f) * 45.0f;
		float x = SpawnLocation.X + ((FMath::FRandRange(0.0f, 300.0f) + 400.0f) * cos(Theta));
		float y = SpawnLocation.Y + ((FMath::FRandRange(0.0f, 300.0f) + 400.0f) * sin(Theta));

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		if (FMath::FRandRange(0.0f, 8.0f) > 5) s = World->SpawnActor<AViking_Ram_Ship>(FVector(x, y, 60.0f), FRotator(0.0f, Theta, 0.0f), param);
		else s = World->SpawnActor<AViking_Shoot_Ship>(FVector(x, y, 60.0f), FRotator(0.0f, Theta, 0.0f), param);

		if (s) {
			s->SetActorRelativeLocation(FVector(x, y, SpawnLocation.Z));
			Camp.Push(s);
		}
	}
}

// Called every frame
void AEnemy_Camp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Bobbing += 5.0f * DeltaTime;
	//Ocean Bobbing
	SetActorLocation(FVector(SpawnLocation.X, SpawnLocation.Y , SpawnLocation.Z + sinf(Bobbing) * 30.0f));

	for (int i = 0; i < Camp.Num(); ++i) {
		if (Camp[i]->IsPendingKillOrUnreachable()) {
			Camp.RemoveAt(i);
		}
		else Camp[i]->Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	}

	if (Camp.Num() == 0) {
		Tags.Add(FName("Completed"));
	}
}

UFUNCTION() void AEnemy_Camp::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {

	//Checking if the other collider is active
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		//First Checking if the enemy array is clear (the player has killed all enemies)
		if (Camp.Num() == 0) {
			//Getting the other objects tag array (player should have the "Player" tag)
			for (const auto it : OtherActor->Tags) {
				if (it == FName("Player")) {
					//UE_LOG(LogTemp, Warning, TEXT("TREASURE HIT"));
					break;
				}
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("THERE ARE STILL %d ENEMIES!"), Camp.Num());
	}
}

