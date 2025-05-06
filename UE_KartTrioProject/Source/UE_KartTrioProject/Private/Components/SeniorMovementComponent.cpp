// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SeniorMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "Net/UnrealNetwork.h"

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
	if (!personalOwner || !personalOwner->IsLocallyControlled())return;
	//if (GetWorld()->GetFirstPlayerController()->GetPawn() != GetOwner())return;
	Move();
	ApplyDeceleration();
	ApplyFovModificationsBasedOnSpeed();
	ApplyCameraSpringArmRotationBasedOnSteer();
	ManageSlipping(DeltaTime);
	DrawDebugs();
}

void USeniorMovementComponent::Init()
{
	InitFields();
	InitEvents();
	InitTimers();
}

void USeniorMovementComponent::InitFields()
{
	personalOwner = Cast<ASeniorPlayer>(GetOwner());
	InitSceneComponents();
	initialForwardMaxSpeed = forwardMaxSpeed;
	initialBackwardMaxSpeed = backwardMaxSpeed;

	if (!personalOwner)return;
	ownersCameraComponent = personalOwner->GetComponentByClass<UCameraComponent>();
	ownersSpringArmComponent = personalOwner->GetComponentByClass<USpringArmComponent>();
	ownersCharacterMovementComponent = personalOwner->GetComponentByClass<UCharacterMovementComponent>();

	initialCameraFov = ownersCameraComponent->FieldOfView;
	if (!fullCartBody || !leftFrontWheel || !rightFrontWheel)return;
	currentPackageNetwork = FPersonalPackageNetwork(personalOwner->GetTransform(), fullCartBody->GetRelativeRotation(), leftFrontWheel->GetRelativeRotation(), rightFrontWheel->GetRelativeRotation(),
		personalOwner->GetLocalActorID());
}

void USeniorMovementComponent::InitEvents()
{
	onMoveForwardDone.AddDynamic(this, &USeniorMovementComponent::LerpRotationToMatchForward);
	onMoveBackwardDone.AddDynamic(this, &USeniorMovementComponent::LerpRotationToMatchSymetricalForward);
	onMovementDone.AddDynamic(this, &USeniorMovementComponent::LerpSteeringToMatchZero);
	onMovementDone.AddDynamic(this, &USeniorMovementComponent::UpdateMeshRotationYaw);
	//onMovementDone.AddDynamic(this, &USeniorMovementComponent::AskForNetworkTransformUpdate);
}

void USeniorMovementComponent::InitSceneComponents()
{
	if (personalOwner)
	{
		fullCartBody = personalOwner->GetCartCapsuleComponent();
		leftFrontWheel = personalOwner->GetLeftFrontWheel();
		rightFrontWheel = personalOwner->GetRightFrontWheel();
	}	
}

void USeniorMovementComponent::InitTimers()
{
	if (!personalOwner || !personalOwner->IsLocallyControlled())return;
	FTimerHandle _networkTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_networkTimerHandle, this, &USeniorMovementComponent::ReplicateTransform, networkUpdateTimerMS / 1000.f, true);
}

void USeniorMovementComponent::Move()
{
	if (!canMove || !ownersCharacterMovementComponent) return;

	if (currentVelocity > 0)
	{
		ownersCharacterMovementComponent->AddInputVector(GetForwardVectorRotatedBySteerAngle() * (currentVelocity/forwardMaxSpeed) /** GetWorld()->DeltaTimeSeconds*/);
		onMoveForwardDone.Broadcast();
	}
	else if (currentVelocity < 0)
	{
		ownersCharacterMovementComponent->AddInputVector(GetSymetricalForwardVectorRotatedBySteerAngle() * (currentVelocity/backwardMaxSpeed/2)/** GetWorld()->DeltaTimeSeconds*/);
		onMoveBackwardDone.Broadcast();
	}
	else
		return;
	onSpeedUpdate.Broadcast(currentVelocity);
	//ownersCharacterMovementComponent->AddInputVector(GetForwardVectorRotatedBySteerAngle() * _currentSpeed);
	onMovementDone.Broadcast();
	
}

void USeniorMovementComponent::ApplyDeceleration()
{
	if(!ownersCharacterMovementComponent ||(isMovingForward || isMovingBackward)) return;
	SetCurrentVelocity(FMath::FInterpConstantTo(currentVelocity, 0, GetWorld()->DeltaTimeSeconds, automaticDecelerationSpeed));
}

void USeniorMovementComponent::ApplyFovModificationsBasedOnSpeed()
{
	ownersCameraComponent->SetFieldOfView(currentVelocity <= 0 ? initialCameraFov : FMath::Lerp(initialCameraFov, initialCameraFov + cameraFovMaximumIncrement, currentVelocity / forwardMaxSpeed));
}

void USeniorMovementComponent::ApplyCameraSpringArmRotationBasedOnSteer()
{
	if (!ownersSpringArmComponent)return;
	FRotator _currentRelRot = ownersSpringArmComponent->GetRelativeRotation();
	// Lerp 0 to cameraAngleOnMaxSteering 
	ownersSpringArmComponent->SetRelativeRotation(FRotator(_currentRelRot.Pitch, 0, _currentRelRot.Roll) + 
		FRotator(0, 1, 0) * FMath::Lerp(0, cameraAngleOnMaxSteering, currentSteeringAngle / maxFrontWheelSteeringAngle), false);
}

void USeniorMovementComponent::AddVelocity(const FInputActionValue& _valuePosFloat)
{
	if (!canMove) return;
	float _newValue = currentVelocity + forwardAccelerationSpeed * GetWorld()->DeltaTimeSeconds;
	SetCurrentVelocity(FMath::Clamp(_newValue, -backwardMaxSpeed, forwardMaxSpeed));

}

void USeniorMovementComponent::SubstractVelocity(const FInputActionValue& _valueFloat)
{
	if (!canMove ||  isMovingForward) return;
	float _newValue = 0;
	if (currentVelocity > 0)
		_newValue = currentVelocity - brakeSpeed * GetWorld()->DeltaTimeSeconds;
	else
		_newValue = currentVelocity - backwardAccelerationSpeed * GetWorld()->DeltaTimeSeconds;

	SetCurrentVelocity(FMath::Clamp(_newValue, -backwardMaxSpeed, forwardMaxSpeed));
}

void USeniorMovementComponent::SteerWheels(const FInputActionValue& _valueFloat)
{
	if (!canSteerWheels || (currentVelocity == 0) /*|| isSlipping*/) return;
	currentSteeringAngle += _valueFloat.Get<float>() * steeringSpeed * GetWorld()->DeltaTimeSeconds;
	currentSteeringAngle = FMath::Clamp(currentSteeringAngle, -maxFrontWheelSteeringAngle, maxFrontWheelSteeringAngle);

	////fsdfs;
	//FMath::Lerp(minimumSteeringSpeed * (currentVelocity< 0 ? -1 : 1) ,_valueFloat.Get<float>() * steeringSpeed * GetWorld()->DeltaTimeSeconds, currentVelocity /
	//	(currentVelocity < 0 ? (backwardMaxSpeed * -1) : forwardMaxSpeed));
	//currentSteeringAngle = FMath::Clamp(currentSteeringAngle, -maxFrontWheelSteeringAngle, maxFrontWheelSteeringAngle);

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
	if (!personalOwner || personalOwner->GetActorForwardVector().Equals(_vectorToMatch, .1f))return;
	const FVector& _personalOwnersLocation = personalOwner->GetActorLocation();
	const FRotator _targetRotation = UKismetMathLibrary::FindLookAtRotation(_personalOwnersLocation, _vectorToMatch + _personalOwnersLocation);
	personalOwner->SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(personalOwner->GetActorRotation(), _targetRotation, GetWorld()->DeltaTimeSeconds, toForwardRotationLerpSpeed));
}

void USeniorMovementComponent::LerpSteeringToMatchZero()
{
	if (!isMovingForward && !isMovingBackward ||UKismetMathLibrary::Abs(currentSteeringAngle) <= 0.1 || isSlipping)return;
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

void USeniorMovementComponent::StopMoveAndRotateTime(const float _time)
{
	FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]()
		{
			SetCanMove(true);
			SetCanRotate(true);
			isStun = false;
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, _time, false);

	isStun = true;
	SetCanMove(false);
	SetCanRotate(false);
}

void USeniorMovementComponent::Slip(const FSlipperySettings& _slipSettings)
{
	initialSteeringSpeed = steeringSpeed;
	isSlipping = true;
	chosenSlipSettings = _slipSettings;
	steeringSpeed = initialSteeringSpeed * chosenSlipSettings.losingControlOverSteeringRation;
	currentSlipTime = 0;
	currentSlipSpeed = _slipSettings.slipSpeed;
	RandomizeSteeringAngleTarget();
}

void USeniorMovementComponent::ManageSlipping(const float _deltaTime)
{
	if (!isSlipping)return;
	currentSlipTime += _deltaTime;
	currentSlipSpeed = FMath::Lerp(chosenSlipSettings.slipSpeed, chosenSlipSettings.slipSpeed/2, currentSlipTime / chosenSlipSettings.slipTime);
	currentSteeringAngle = FMath::FInterpConstantTo(currentSteeringAngle, steeringAngleSlipTarget, _deltaTime, currentSlipSpeed); //TODO CHANGE AND MAKE THE SLIPPING LOGIC HERE

	if (currentSteeringAngle == steeringAngleSlipTarget) RandomizeSteeringAngleTarget();

	if (currentSlipTime > chosenSlipSettings.slipTime)
	{
		isSlipping = false;
		steeringSpeed = initialSteeringSpeed;
	}
}


void USeniorMovementComponent::RandomizeSteeringAngleTarget()
{
	steeringAngleSlipTarget = (FMath::RandBool() ? 1 : -1) * FMath::FRandRange(maxFrontWheelSteeringAngle / 4.f, maxFrontWheelSteeringAngle);
}

void USeniorMovementComponent::DrawDebugs()
{
	if (!useDebugs || !personalOwner)return;
	const FVector& _currentLoc = personalOwner->GetActorLocation();
	const FVector& _rotatedForwardVector = GetForwardVectorRotatedBySteerAngle();
	DrawDebugDirectionalArrow(GetWorld(), _currentLoc, _currentLoc + _rotatedForwardVector * arrowWheelDirectionLength, 10, FColor::Magenta);
	const FVector& _rotatedBackwardVector = -GetSymetricalForwardVectorRotatedBySteerAngle();
	DrawDebugDirectionalArrow(GetWorld(), _currentLoc, _currentLoc + _rotatedBackwardVector * arrowWheelDirectionLength, 10, FColor::Yellow);

}

void USeniorMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USeniorMovementComponent, currentVelocity);
	DOREPLIFETIME_CONDITION_NOTIFY(USeniorMovementComponent, currentPackageNetwork, COND_None, REPNOTIFY_Always);
}

void USeniorMovementComponent::OnRep_CurrentTransform()
{
	if (!personalOwner || !fullCartBody || !leftFrontWheel || !rightFrontWheel ||
		personalOwner->GetLocalActorID() == currentPackageNetwork.localCharacterID) return; //if the local id corresponds to this one, we dont want to set the transform since it has already been done
	personalOwner->SetActorTransform(currentPackageNetwork.currentActorTransform);
	fullCartBody->SetRelativeRotation(currentPackageNetwork.fullCartRelativeRot);
	leftFrontWheel->SetRelativeRotation(currentPackageNetwork.leftFrontWheelRelativeRot);
	rightFrontWheel->SetRelativeRotation(currentPackageNetwork.rightFrontWheelRelativeRot);
}

void USeniorMovementComponent::SetCurrentVelocityServer_Implementation(const float _value)
{
	currentVelocity = _value;
}

void USeniorMovementComponent::ReplicateTransform()
{
	if (!personalOwner || !fullCartBody || !leftFrontWheel || !rightFrontWheel) return;
	currentPackageNetwork = FPersonalPackageNetwork(personalOwner->GetTransform(), fullCartBody->GetRelativeRotation(), leftFrontWheel->GetRelativeRotation(), rightFrontWheel->GetRelativeRotation(),
		personalOwner->GetLocalActorID());
	if (!personalOwner->HasAuthority())
		ReplicateTransformServer(currentPackageNetwork);
}


void USeniorMovementComponent::ReplicateTransformServer_Implementation(const FPersonalPackageNetwork& _package)
{
	currentPackageNetwork = _package;
	OnRep_CurrentTransform();
}
