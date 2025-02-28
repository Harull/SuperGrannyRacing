// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <GPE/CollectedItem.h>
#include "GIS_CollectedItem.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UGIS_CollectedItem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<ACollectedItem>> _allCollectedItem;
	
public:
	FORCEINLINE int GetRange() const { return _allCollectedItem.Num(); }

public:
	void AddCollectedItem(TObjectPtr<ACollectedItem> _item);
	void RemoveCollectedItem(TObjectPtr<ACollectedItem> _item);

};
