#include "UI/ArrowSign.h"

AArrowSign::AArrowSign()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void AArrowSign::BeginPlay()
{
	Super::BeginPlay();
	currentPosition = GetActorLocation();
	currentRotation = GetActorRotation();
}

void AArrowSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ArrowMovement(DeltaTime);
}

void AArrowSign::SetPosition(const FVector& _position)
{
	if (_position == GetActorLocation()) return;

	SetActorLocation(_position);
	currentPosition = GetActorLocation();
	currentRotation = GetActorRotation();
}

void AArrowSign::ArrowMovement(float _deltaTime)
{
	timePassed += _deltaTime;
	UpAndDown(_deltaTime);
	Rotate(_deltaTime);
}

void AArrowSign::UpAndDown(float _deltaTime)
{
	FVector _newPosition = currentPosition;
	_newPosition.Z += FMath::Sin(timePassed) * upDownSpeed;
	SetActorLocation(_newPosition);
}

void AArrowSign::Rotate(float _deltaTime)
{
	FRotator _newRotation = GetActorRotation();
	_newRotation.Yaw += _deltaTime * rotateSpeed;

	SetActorRotation(_newRotation);
}