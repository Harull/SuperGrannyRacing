// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE/OverlapObject.h"
#include "CollectedItem.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API ACollectedItem : public AOverlapObject
{
	GENERATED_BODY()
	
public:
	ACollectedItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction() override;
};
