// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputAction.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <SeniorPlayer.h>
#include "SeniorMovementComponent.generated.h"


USTRUCT()
struct FPersonalPackageNetwork
{
	GENERATED_BODY()

public:
	UPROPERTY() FTransform currentActorTransform;
	UPROPERTY() FRotator fullCartRelativeRot;
	UPROPERTY() FRotator leftFrontWheelRelativeRot;
	UPROPERTY() FRotator rightFrontWheelRelativeRot;
	UPROPERTY() uint32 localCharacterID;

	FPersonalPackageNetwork() = default;

	FPersonalPackageNetwork(const FTransform& currentActorTransform, const FRotator& fullCartRelativeRot, const FRotator& leftFrontWheelRelativeRot, const FRotator& rightFrontWheelRelativeRot, const uint32& localCharacterID)
		: currentActorTransform(currentActorTransform), fullCartRelativeRot(fullCartRelativeRot), leftFrontWheelRelativeRot(leftFrontWheelRelativeRot), rightFrontWheelRelativeRot(rightFrontWheelRelativeRot), localCharacterID(localCharacterID)
	{
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API USeniorMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementDone);
	FOnMovementDone onMovementDone;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveForwardDone);
	FOnMoveForwardDone onMoveForwardDone;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveBackwardDone);
	FOnMoveBackwardDone onMoveBackwardDone;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedUpdate, float, _speed);
	FOnSpeedUpdate onSpeedUpdate;

	UPROPERTY() TObjectPtr<USceneComponent> fullCartBody;
	UPROPERTY() TObjectPtr<USceneComponent> leftFrontWheel;
	UPROPERTY() TObjectPtr<USceneComponent> rightFrontWheel;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float forwardMaxSpeed = 20;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess)) float initialForwardMaxSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float backwardMaxSpeed = 10;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess)) float initialBackwardMaxSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float forwardAccelerationSpeed = 100;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float automaticDecelerationSpeed = 10;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float brakeSpeed = 70;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float backwardAccelerationSpeed = 50;


	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float steeringSpeed = 10;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float toForwardRotationLerpSpeed = 50;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters|Movement") float toNormalSteeringAngleLerpSpeed = 25;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10", UIMin = 10), Category = "Parameters|Movement") float maxFrontWheelSteeringAngle = 45;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10", UIMin = 10, Units ="ms"), Category = "Parameters|NetWork") float networkUpdateTimerMS = 45;

	UPROPERTY(EditAnywhere, Category = "Debug") bool useDebugs = true;
	UPROPERTY(EditAnywhere, Category = "Debug") float arrowWheelDirectionLength = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Movement") float currentSteeringAngle = 0;
	UPROPERTY(EditAnywhere, Category = "Debug|Movement") bool canMove = true;
	UPROPERTY(EditAnywhere, Category = "Debug|Movement") bool canRotate = true;
	UPROPERTY(EditAnywhere, Category = "Debug|Movement") bool canSteerWheels = true;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Movement") bool isMovingForward = false;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Movement") bool isMovingBackward = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|Movement", meta = (AllowPrivateAccess), Replicated) float currentVelocity = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Movement", meta = (AllowPrivateAccess), ReplicatedUsing = OnRep_CurrentTransform) FPersonalPackageNetwork currentPackageNetwork;


	UPROPERTY() TObjectPtr<ASeniorPlayer> personalOwner;
	UPROPERTY() TObjectPtr<UCharacterMovementComponent> ownersCharacterMovementComponent;


public:	
	USeniorMovementComponent();

public:
	FORCEINLINE FOnSpeedUpdate& OnSpeedUpdate() { return onSpeedUpdate; }


	FORCEINLINE FVector GetForwardVectorRotatedBySteerAngle() const { return GetOwner()->GetActorForwardVector().RotateAngleAxis(currentSteeringAngle, FVector::UpVector); }
	FORCEINLINE FVector GetSymetricalForwardVectorRotatedBySteerAngle() const { return GetOwner()->GetActorForwardVector().RotateAngleAxis(-currentSteeringAngle, FVector::UpVector); }

	FORCEINLINE void SetCanMove(const bool _value) { canMove = _value; }
	FORCEINLINE void SetCanRotate(const bool _value) { canRotate = _value; }
	FORCEINLINE void SetCanSteerWheels(const bool _value) { canSteerWheels = _value; }

	FORCEINLINE void SetForwardMaxSpeed(const float _value) { forwardMaxSpeed = _value; }
	FORCEINLINE void SetBackwardMaxSpeed(const float _value) { backwardMaxSpeed = _value; }

	FORCEINLINE float GetForwardMaxSpeed() const { return forwardMaxSpeed; }
	FORCEINLINE float GetBackwardMaxSpeed() const { return backwardMaxSpeed; }

	FORCEINLINE void ResetForwardMaxSpeed() { forwardMaxSpeed = initialForwardMaxSpeed; }
	FORCEINLINE void ResetBackwardMaxSpeed() { backwardMaxSpeed = initialBackwardMaxSpeed; }
	
	FORCEINLINE void SetCurrentVelocity(const float _value) 
	{
		currentVelocity = _value;
		if (!GetOwner()->HasAuthority())
			SetCurrentVelocityServer(_value);
	}

	FORCEINLINE void ResetVelocity() { SetCurrentVelocity(0); }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Init();
	void InitFields();
	void InitEvents();
	void InitSceneComponents();
	void InitTimers();

private:
	void Move();
	void ApplyDeceleration();

public:
	//Binded externaly to inputs

	UFUNCTION() void AddVelocity(const FInputActionValue& _valuePosFloat);
	UFUNCTION() void SubstractVelocity(const FInputActionValue& _valueFloat);
	UFUNCTION() void SteerWheels(const FInputActionValue& _valueFloat);
	UFUNCTION() void SetIsMovingForward(const FInputActionValue& _valueFloat);
	UFUNCTION() void SetIsMovingBackward(const FInputActionValue& _valueFloat);
	//Binded externaly to inputs

	//Not used for movement, but for outside only
	
	void StopMoveAndRotateTime(const float _time);

private:
	UFUNCTION() void LerpRotationToMatchForward();
	UFUNCTION() void LerpRotationToMatchSymetricalForward();
	UFUNCTION() void LerpRotationToMatchVector(const FVector& _vectorToMatch);
	UFUNCTION() void LerpSteeringToMatchZero();
	UFUNCTION() void UpdateMeshRotationYaw();
private:
	void DrawDebugs();

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION() void OnRep_CurrentTransform();

	UFUNCTION(Server, Unreliable) void SetCurrentVelocityServer(const float _value);

	UFUNCTION() void ReplicateTransform();
	UFUNCTION(Server, Unreliable) void ReplicateTransformServer(const FPersonalPackageNetwork& _package);

};
