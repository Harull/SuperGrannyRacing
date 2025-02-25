// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SeniorMovementComponent.h"

// Sets default values for this component's properties
USeniorMovementComponent::USeniorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USeniorMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}


// Called every frame
void USeniorMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DrawDebugs();
}

void USeniorMovementComponent::Init()
{
	InitFields();
}

void USeniorMovementComponent::InitFields()
{
	personalOwner = GetOwner();
	ownersCharacterMovementComponent = personalOwner->GetComponentByClass<UCharacterMovementComponent>();
}

void USeniorMovementComponent::MoveForward(const FInputActionValue& _valuePosFloat)
{
	if (!canMove || !ownersCharacterMovementComponent) return;
	ownersCharacterMovementComponent->AddInputVector(GetForwardVectorRotatedBySteerAngle() * forwardSpeed * GetWorld()->DeltaTimeSeconds);
}

void USeniorMovementComponent::MoveBackward(const FInputActionValue& _valueNegFloat)
{
	if (!canMove || !ownersCharacterMovementComponent) return;
	ownersCharacterMovementComponent->AddInputVector(-GetForwardVectorRotatedBySteerAngle() * backwardSpeed * GetWorld()->DeltaTimeSeconds);
}

void USeniorMovementComponent::SteerWheels(const FInputActionValue& _valueFloat)
{
	if (!canSteerWheels) return;
	currentSteeringAngle += _valueFloat.Get<float>() * steeringSpeed * GetWorld()->GetDeltaSeconds();
	currentSteeringAngle = FMath::Clamp(currentSteeringAngle, -maxFrontWheelSteeringAngle, maxFrontWheelSteeringAngle);
}

void USeniorMovementComponent::DrawDebugs()
{
	if (!useDebugs)return;
	const FVector& _currentLoc = personalOwner->GetActorLocation();
	const FVector& _rotatedForwardVector = GetForwardVectorRotatedBySteerAngle();
	DrawDebugDirectionalArrow(GetWorld(), _currentLoc, _currentLoc + _rotatedForwardVector * arrowWheelDirectionLength, 10, FColor::Magenta);
}

