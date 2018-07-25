// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShip.h"
#include "PlayerProjectile.h"


#include "TimerManager.h"
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

const FName APlayerShip::MoveForwardBinding("MoveForward");
const FName APlayerShip::MoveRightBinding("MoveRight");
const FName APlayerShip::FireForwardBinding("FireForward");
const FName APlayerShip::FireRightBinding("FireRight");
const FName APlayerShip::FireMouseBinding("MouseFire");
// Sets default values
APlayerShip::APlayerShip()
{
	bFiring = false;
	bCanFire = true;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = { 0.0f, 0.0f, 0.0f };
	MaxSpeed = 5.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;

	//Ship Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Boat/OC_Boat.OC_Boat'")).Object);
	ShipMesh->SetSimulatePhysics(false);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	ShipMesh->SetWorldScale3D(FVector(40.0f, -40.0f, 40.0f));
	RootComponent = ShipMesh;

	//Steer Viking Mesh
	Viking_Steer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Viking"));
	Viking_Steer->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("AnimSequence'/Game/VikingAssets/Animation/Anim_Steering_Anim.Anim_Steering_Anim'")).Object);
	Viking_Steer->SetupAttachment(RootComponent);
	Viking_Steer->SetSimulatePhysics(false);
	Viking_Steer->SetRelativeTransform(FTransform(FVector(0.0f, 2.0f, 0.5f)));
	Viking_Steer->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f), false, false);


	//SteerAnim

	static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Game/VikingAssets/Animation/Anim_Steering_Anim.Anim_Steering_Anim'"));
	Anim = anim.Object;


	//Throw Viking Mesh
	Viking_Throw = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Throwing Viking"));
	Viking_Throw->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Thrower/ThrowViking.ThrowViking'")).Object);
	Viking_Throw->SetupAttachment(RootComponent);
	Viking_Throw->SetSimulatePhysics(false);
	Viking_Throw->SetRelativeTransform(FTransform(FVector(0.0f, -2.0f, 0.5f)));
	Viking_Throw->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f), false, false);

	//Rudder 0
	Ship_Rudder_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Rudder"));
	Ship_Rudder_Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Boat/Rudders.Rudders'")).Object);
	Ship_Rudder_Mesh->SetupAttachment(RootComponent);
	Ship_Rudder_Mesh->SetSimulatePhysics(false);
	Ship_Rudder_Mesh->SetRelativeScale3D(FVector(10.1f, 10.1f, 10.1f));
	Ship_Rudder_Mesh->SetRelativeTransform(FTransform(FVector(0.0f, 2.3f, 1.0f)));
	Ship_Rudder_Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);

	fCurrentTurnRate = 0.0f;
	fMaxTurnRate = 1.0f;
	fCurrentSpeed = 0.0f;
	fMaxSpeed = 6.0f;
	fMaxBackSpeed = 3.0f;
	fFacingDegree = 0;

	// Create a camera boom...
	Camera_Springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	Camera_Springarm->SetupAttachment(RootComponent);
	Camera_Springarm->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	Camera_Springarm->TargetArmLength = 2000.f;
	Camera_Springarm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	Camera_Springarm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

												// Create a camera...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(Camera_Springarm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	GunOffset = FVector(170.f, 0.f, 0.f);
	FireRate = 0.1f;
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "USING PLAYER SHIP");
}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Movement(DeltaTime);
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	float fMouseX;
	float fMouseY;
	int iWidth;
	int iHeight;
	MyController->GetMousePosition(fMouseX, fMouseY);
	MyController->GetViewportSize(iWidth, iHeight);
	fMouseX = fMouseX - (iWidth / 2);
	fMouseY = fMouseY - (iHeight / 2);
	FVector FireDirection = FVector(fMouseX, fMouseY, 0.f);
	FireDirection = FireDirection.RotateAngleAxis(90, FVector(0, 0, 1));

	FireShot(FireDirection);

}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
	PlayerInputComponent->BindAction("MouseFire", IE_Pressed, this, &APlayerShip::FiringShot);
	PlayerInputComponent->BindAction("MouseFire", IE_Released, this, &APlayerShip::StopingFire);

	MyController = Cast<APlayerController>(GetController());
	if (MyController)
	{
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
	}
}

void APlayerShip::Movement(float DeltaSeconds)
{
	ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0)
	{
		if (abs(fCurrentTurnRate) < fMaxTurnRate)
		{
			if (RightValue > 0) fCurrentTurnRate += (0.01 * ForwardValue);
			else if (RightValue < 0) fCurrentTurnRate -= (0.01 * ForwardValue);
		}
		else fCurrentTurnRate = (fCurrentTurnRate / abs(fCurrentTurnRate)) * fMaxTurnRate;

		fFacingDegree += fCurrentTurnRate;
	}
	else
	{
		if (abs(fCurrentTurnRate) <= fMaxTurnRate)
		{
			if (RightValue > 0) fCurrentTurnRate += 0.01;
			else if (RightValue < 0) fCurrentTurnRate -= 0.01;
		}
		else fCurrentTurnRate = (fCurrentTurnRate / abs(fCurrentTurnRate)) * fMaxTurnRate;

		fFacingDegree += fCurrentTurnRate;
	}
	if (RightValue == 0)
	{
		if (fCurrentTurnRate < 0) fCurrentTurnRate += 0.01;
		else if (fCurrentTurnRate > 0) fCurrentTurnRate -= 0.01;
	}

	if ((abs(fCurrentTurnRate)) < 0.005) fCurrentTurnRate = 0.0f;

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	FVector MoveDirection = FVector(1.0f, 0.0f, 0.f).GetClampedToMaxSize(1.0f);
	FVector AxisVector = FVector(0, 0, 1);
	MoveDirection = MoveDirection.RotateAngleAxis(fFacingDegree, AxisVector);

	// Calculate  movement
	const FVector Movement = MoveDirection;
	FHitResult Hit(1.f);
	FQuat QRotation = FQuat(FRotator(0, fFacingDegree - 90, 0));

	SetActorRotation(QRotation, ETeleportType::None);
	// If non-zero size, move this actor
	if ((abs(fCurrentSpeed)) > 0 || Movement.SizeSquared() > 0)
	{
		if (fCurrentSpeed <= fMaxSpeed && fCurrentSpeed >= -fMaxBackSpeed)
		{
			if (ForwardValue > 0) fCurrentSpeed += 0.1;
			else if (ForwardValue < 0) fCurrentSpeed -= 0.1;
		}
		if (ForwardValue == 0)
		{
			if (fCurrentSpeed < 0) fCurrentSpeed += 0.1;
			else if (fCurrentSpeed > 0) fCurrentSpeed -= 0.1;
		}
		RootComponent->MoveComponent(Movement * fCurrentSpeed, QRotation, true, &Hit);
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, QRotation, true);
		}
	}
	if ((abs(fCurrentSpeed)) < 0.05) fCurrentSpeed = 0.0f;
}

void APlayerShip::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bFiring == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<APlayerProjectile>(SpawnLocation, FireRotation);
			}

			bFiring = false;
			//World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &APlayerShip::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bFiring = false;
		}
	}
}

void APlayerShip::FiringShot()
{
	bFiring = true;
}
void APlayerShip::StopingFire()
{
	bFiring = false;
}


void APlayerShip::ShotTimerExpired()
{

	bCanFire = true;
}



