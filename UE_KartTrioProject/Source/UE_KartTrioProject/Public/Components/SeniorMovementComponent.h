// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeniorMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API USeniorMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	bool canMove = true;
	bool canRotate = true;


public:	
	USeniorMovementComponent();

public:
	FORCEINLINE void SetCanMove(const bool _value) { canMove = _value; }
	FORCEINLINE void SetCanRotate(const bool _value) { canRotate = _value; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Move(FInputKEKCHOSE);

};
