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
	UPROPERTY(EditAnywhere) float timeStun = 2.f;
	
public:
	APuddle();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction() override;

};
