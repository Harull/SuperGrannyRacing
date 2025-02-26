// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputMappingContext.h>
#include <Components/SeniorMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/CapsuleComponent.h"
#include <Camera/CameraComponent.h>

#include "SeniorPlayer.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API ASeniorPlayer : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<USeniorMovementComponent> seniorMovementcomponent;
	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera;


	UPROPERTY(EditAnywhere) TObjectPtr<UCapsuleComponent> cartCapsuleComponent;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> shoppingCart;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> backWheels;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> frontRightWheel;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> frontLeftWheel;


	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> mapping;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> forward;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> backward;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> steering;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> interact;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> usePowerup;

	
public:
	ASeniorPlayer();

public:
	FORCEINLINE TObjectPtr<UCapsuleComponent> GetCartCapsuleComponent()const { return cartCapsuleComponent; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetLeftFrontWheel()const { return frontLeftWheel; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetRightFrontWheel()const { return frontRightWheel; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void InitSubsystem();
	void InitInputs(TObjectPtr<UEnhancedInputComponent> _inputComponent);

private:

};
