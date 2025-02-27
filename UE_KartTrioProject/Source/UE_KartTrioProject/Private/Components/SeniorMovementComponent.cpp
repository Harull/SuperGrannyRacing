// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SeniorMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include <SeniorPlayer.h>

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
	//ownersSkeletalMesh->SetWorldRotation(UKismetMathLibrary::RInterpTo_Constant(ownersSkeletalMesh->GetComponentRotation(), 
	//	UKismetMathLibrary::FindLookAtRotation(ownersSkeletalMesh->GetComponentLocation(), ownersSkeletalMesh->GetComponentLocation() + )))
}

void USeniorMovementComponent::Init()
{
	InitFields();
	InitEvents();
	InitSceneComponents();
}

void USeniorMovementComponent::InitFields()
{
	personalOwner = GetOwner();
	ownersCharacterMovementComponent = personalOwner->GetComponentByClass<UCharacterMovementComponent>();
	initialForwardSpeed = forwardSpeed;
	initialBackwardSpeed = backwardSpeed;
}

void USeniorMovementComponent::InitEvents()
{
	onMoveForwardDone.AddDynamic(this, &USeniorMovementComponent::LerpRotationToMatchForward);
	onMoveBackwardDone.AddDynamic(this, &USeniorMovementComponent::LerpRotationToMatchSymetricalForward);
	onMovementDone.AddDynamic(this, &USeniorMovementComponent::LerpSteeringToMatchZero);
	onMovementDone.AddDynamic(this, &USeniorMovementComponent::UpdateMeshRotationYaw);
}

void USeniorMovementComponent::InitSceneComponents()
{
	if (TObjectPtr<ASeniorPlayer> _playerAsSenior = Cast<ASeniorPlayer>(personalOwner))
	{
		fullCartBody = _playerAsSenior->GetCartCapsuleComponent();
		leftFrontWheel = _playerAsSenior->GetLeftFrontWheel();
		rightFrontWheel = _playerAsSenior->GetRightFrontWheel();
	}	
}

void USeniorMovementComponent::MoveForward(const FInputActionValue& _valuePosFloat)
{
	if (!canMove || !ownersCharacterMovementComponent) return;
	ownersCharacterMovementComponent->AddInputVector(GetForwardVectorRotatedBySteerAngle() * forwardSpeed * GetWorld()->DeltaTimeSeconds);
	onMovementDone.Broadcast();
	onMoveForwardDone.Broadcast();
}

void USeniorMovementComponent::MoveBackward(const FInputActionValue& _valueFloat)
{
	if (!canMove || !ownersCharacterMovementComponent || isMovingForward) return;
	ownersCharacterMovementComponent->AddInputVector(-GetSymetricalForwardVectorRotatedBySteerAngle() * backwardSpeed * GetWorld()->DeltaTimeSeconds);
	onMovementDone.Broadcast();
	onMoveBackwardDone.Broadcast();
}

void USeniorMovementComponent::SteerWheels(const FInputActionValue& _valueFloat)
{
	if (!canSteerWheels || (!isMovingForward && !isMovingBackward)) return;
	currentSteeringAngle += _valueFloat.Get<float>() * steeringSpeed * GetWorld()->GetDeltaSeconds();
	currentSteeringAngle = FMath::Clamp(currentSteeringAngle, -maxFrontWheelSteeringAngle, maxFrontWheelSteeringAngle);
}

void USeniorMovementComponent::SetIsMovingForward(const FInputActionValue& _valueFloat)
{
	isMovingForward = _valueFloat.Get<float>() >= 0.01;
}

void USeniorMovementComponent::SetIsMovingBackward(const FInputActionValue& _valueFloat)
{
	isMovingBackward = _valueFloat.Get<float>() >= 0.01;
}

void USeniorMovementComponent::LerpRotationToMatchForward()
{
	LerpRotationToMatchVector(GetForwardVectorRotatedBySteerAngle());
}

void USeniorMovementComponent::LerpRotationToMatchSymetricalForward()
{
	LerpRotationToMatchVector(GetSymetricalForwardVectorRotatedBySteerAngle());
}

void USeniorMovementComponent::LerpRotationToMatchVector(const FVector& _vectorToMatch)
{
	if (personalOwner->GetActorForwardVector().Equals(_vectorToMatch, .1f))return;
	const FVector& _personalOwnersLocation = personalOwner->GetActorLocation();
	const FRotator _targetRotation = UKismetMathLibrary::FindLookAtRotation(_personalOwnersLocation, _vectorToMatch + _personalOwnersLocation);
	personalOwner->SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(personalOwner->GetActorRotation(), _targetRotation, GetWorld()->DeltaTimeSeconds, toForwardRotationLerpSpeed));
}

void USeniorMovementComponent::LerpSteeringToMatchZero()
{
	if (UKismetMathLibrary::Abs(currentSteeringAngle) <= 0.1)return;
	currentSteeringAngle = UKismetMathLibrary::FInterpTo_Constant(currentSteeringAngle, 0, GetWorld()->DeltaTimeSeconds, toNormalSteeringAngleLerpSpeed);
}

void USeniorMovementComponent::UpdateMeshRotationYaw()
{
	const FRotator& _halfSteeringYaw = FRotator(0, 0, -currentSteeringAngle / 2.f); //Note to self, seems like the cart mesh rotation are fcked up, normally we want the yaw modified, but the yaw is fckd
	if (fullCartBody)
		fullCartBody->SetRelativeRotation(FRotator(0, 0, -currentSteeringAngle / 2.f) + FRotator(90, 0, 0)); //Here pretty fcked up
	if(leftFrontWheel)
		leftFrontWheel->SetRelativeRotation(FRotator(0, currentSteeringAngle / 2.f, 0)); 
	if (rightFrontWheel)
		rightFrontWheel->SetRelativeRotation(FRotator(0, currentSteeringAngle / 2.f, 0));
}

void USeniorMovementComponent::DrawDebugs()
{
	if (!useDebugs)return;
	const FVector& _currentLoc = personalOwner->GetActorLocation();
	const FVector& _rotatedForwardVector = GetForwardVectorRotatedBySteerAngle();
	DrawDebugDirectionalArrow(GetWorld(), _currentLoc, _currentLoc + _rotatedForwardVector * arrowWheelDirectionLength, 10, FColor::Magenta);
	const FVector& _rotatedBackwardVector = -GetSymetricalForwardVectorRotatedBySteerAngle();
	DrawDebugDirectionalArrow(GetWorld(), _currentLoc, _currentLoc + _rotatedBackwardVector * arrowWheelDirectionLength, 10, FColor::Yellow);
}

