// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShip.h"

const FName APlayerShip::MoveForwardBinding("MoveForward");
const FName APlayerShip::MoveRightBinding("MoveRight");
const FName APlayerShip::FireForwardBinding("FireForward");
const FName APlayerShip::FireRightBinding("FireRight");

// Sets default values
APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = { 0.0f, 0.0f, 0.0f };
	MaxSpeed = 5.0f;
	MaxForce = 0.5f;
	ApproachRadius = 100.0f;

	//Ship Mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Boat_Placeholder.Boat_Placeholder'")).Object);
	ShipMesh->SetSimulatePhysics(true);
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, -10.0f)));
	ShipMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f), false, false);
	ShipMesh->SetWorldScale3D(FVector(40.0f, -40.0f, 40.0f));
	RootComponent = ShipMesh;

	//Steer Viking Mesh
	Viking_Steer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Viking"));
	Viking_Steer->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Viking_Steering.Viking_Steering'")).Object);
	Viking_Steer->SetupAttachment(RootComponent);
	Viking_Steer->SetSimulatePhysics(false);
	Viking_Steer->SetRelativeTransform(FTransform(FVector(0.0f, 2.0f, 0.5f)));
	Viking_Steer->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f), false, false);

	//Throw Viking Mesh
	Viking_Throw = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Throwing Viking"));
	Viking_Throw->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/VikingAssets/Viking_AxeThrowing.Viking_AxeThrowing'")).Object);
	Viking_Throw->SetupAttachment(RootComponent);
	Viking_Throw->SetSimulatePhysics(false);
	Viking_Throw->SetRelativeTransform(FTransform(FVector(0.0f, -2.0f, 0.5f)));
	Viking_Throw->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f), false, false);

	fCurrentTurnRate = 0.0f;
	fMaxTurnRate = 1.0f;
	fCurrentSpeed = 0.0f;
	fMaxSpeed = 8.0f;
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
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Movement(DeltaTime);
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

