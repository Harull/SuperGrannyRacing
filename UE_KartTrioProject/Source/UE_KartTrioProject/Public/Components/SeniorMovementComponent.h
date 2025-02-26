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

	UPROPERTY() TObjectPtr<USceneComponent> fullCartBody;
	UPROPERTY() TObjectPtr<USceneComponent> leftFrontWheel;
	UPROPERTY() TObjectPtr<USceneComponent> rightFrontWheel;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float forwardSpeed = 20;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float backwardSpeed = 10;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float steeringSpeed = 10;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float toForwardRotationLerpSpeed = 50;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = 0), Category = "Parameters") float toNormalSteeringAngleLerpSpeed = 25;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10", UIMin = 10), Category = "Parameters") float maxFrontWheelSteeringAngle = 45;

	UPROPERTY(EditAnywhere, Category = "Debug") bool useDebugs = true;
	UPROPERTY(EditAnywhere, Category = "Debug") float arrowWheelDirectionLength = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") float currentSteeringAngle = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debug|Values") bool canMove = true, canRotate = true, canSteerWheels = true;

	UPROPERTY() TObjectPtr<AActor> personalOwner;
	UPROPERTY() TObjectPtr<UCharacterMovementComponent> ownersCharacterMovementComponent;

public:	
	USeniorMovementComponent();

public:
	FORCEINLINE FVector GetForwardVectorRotatedBySteerAngle() const { return personalOwner->GetActorForwardVector().RotateAngleAxis(currentSteeringAngle, FVector::UpVector); }

	FORCEINLINE void SetCanMove(const bool _value) { canMove = _value; }
	FORCEINLINE void SetCanRotate(const bool _value) { canRotate = _value; }
	FORCEINLINE void SetCanSteerWheels(const bool _value) { canSteerWheels = _value; }

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
	UFUNCTION() void MoveBackward(const FInputActionValue& _valueNegFloat);
	UFUNCTION() void SteerWheels(const FInputActionValue& _valueFloat);
	UFUNCTION() void LerpRotationToMatchForward();
	UFUNCTION() void LerpSteeringToMatchZero();
	UFUNCTION() void UpdateMeshRotationYaw();

private:
	void DrawDebugs();
};
