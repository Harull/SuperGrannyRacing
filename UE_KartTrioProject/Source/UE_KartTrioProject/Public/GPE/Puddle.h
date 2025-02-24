// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE/OverlapObject.h"
#include "Puddle.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API APuddle : public AOverlapObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APuddle();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction() override;

};
