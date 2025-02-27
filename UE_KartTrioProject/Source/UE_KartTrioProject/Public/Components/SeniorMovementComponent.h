// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputAction.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "SeniorMovementComponent.generated.h"


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

	UPROPERTY() TObjectPtr<USceneComponent> fullCartBody;
	UPROPERTY() TObjectPtr<USceneComponent> leftFrontWheel;
	UPROPERTY() TObjectPtr<USceneComponent> rightFrontWheel;
	//UPROPERTY() TObjectPtr<USceneComponent> rightFrontWheel;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float forwardSpeed = 20;
	float initialForwardSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float backwardSpeed = 10;
	float initialBackwardSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float steeringSpeed = 10;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float toForwardRotationLerpSpeed = 50;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float toNormalSteeringAngleLerpSpeed = 25;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10", UIMin = 10), Category = "Parameters") float maxFrontWheelSteeringAngle = 45;

	UPROPERTY(EditAnywhere, Category = "Debug") bool useDebugs = true;
	UPROPERTY(EditAnywhere, Category = "Debug") float arrowWheelDirectionLength = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") float currentSteeringAngle = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool canMove = true;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool canRotate = true;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool canSteerWheels = true;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool isMovingForward = false;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool isMovingBackward = false;


	UPROPERTY() TObjectPtr<AActor> personalOwner;
	UPROPERTY() TObjectPtr<UCharacterMovementComponent> ownersCharacterMovementComponent;

public:	
	USeniorMovementComponent();

public:
	FORCEINLINE FVector GetForwardVectorRotatedBySteerAngle() const { return personalOwner->GetActorForwardVector().RotateAngleAxis(currentSteeringAngle, FVector::UpVector); }
	FORCEINLINE FVector GetSymetricalForwardVectorRotatedBySteerAngle() const { return personalOwner->GetActorForwardVector().RotateAngleAxis(-currentSteeringAngle, FVector::UpVector); }

	FORCEINLINE void SetCanMove(const bool _value) { canMove = _value; }
	FORCEINLINE void SetCanRotate(const bool _value) { canRotate = _value; }
	FORCEINLINE void SetCanSteerWheels(const bool _value) { canSteerWheels = _value; }

	FORCEINLINE void SetForwardSpeed(const float _value) { forwardSpeed = _value; }
	FORCEINLINE void SetBackwardSpeed(const float _value) { backwardSpeed = _value; }

	FORCEINLINE float GetForwardSpeed() const { return forwardSpeed; }
	FORCEINLINE float GetBackwardSpeed() const { return backwardSpeed; }

	FORCEINLINE void ResetForwardSpeed() { forwardSpeed = initialForwardSpeed; }
	FORCEINLINE void ResetBackwardSpeed() { backwardSpeed = initialBackwardSpeed; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Init();
	void InitFields();
	void InitEvents();
	void InitSceneComponents();

public:
	UFUNCTION() void MoveForward(const FInputActionValue& _valuePosFloat);
	UFUNCTION() void MoveBackward(const FInputActionValue& _valueFloat);
	UFUNCTION() void SteerWheels(const FInputActionValue& _valueFloat);
	UFUNCTION() void SetIsMovingForward(const FInputActionValue& _valueFloat);
	UFUNCTION() void SetIsMovingBackward(const FInputActionValue& _valueFloat);

private:
	UFUNCTION() void LerpRotationToMatchForward();
	UFUNCTION() void LerpRotationToMatchSymetricalForward();
	UFUNCTION() void LerpRotationToMatchVector(const FVector& _vectorToMatch);
	UFUNCTION() void LerpSteeringToMatchZero();
	UFUNCTION() void UpdateMeshRotationYaw();


private:
	void DrawDebugs();
};
