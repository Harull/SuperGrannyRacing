// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <GPE/CollectedItem.h>
#include "Subsystems/WorldSubsystem.h"
#include "GIS_CollectedItem.generated.h"

/**
 *
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UGIS_CollectedItem : public UWorldSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<ACollectedItem>> allCollectedItem; //Tous les collectedItem sur la map
	UPROPERTY() TArray<TObjectPtr<ACollectedItem>> allItemToList; //Tous les collectedItem de la liste de course
public:
	FORCEINLINE int GetRange() const { return allCollectedItem.Num(); }
	FORCEINLINE TArray<TObjectPtr<ACollectedItem>> GetListCollectedItem() const { return allCollectedItem; }
	FORCEINLINE TArray<TObjectPtr<ACollectedItem>> GetListItem() const { return allItemToList; }
	FORCEINLINE bool ItemListIsEmpty() const { return allItemToList.Num() <= 0; }

public:
	void AddCollectedItem(TObjectPtr<ACollectedItem> _item);
	void RemoveCollectedItem(TObjectPtr<ACollectedItem> _item);
	TArray<TObjectPtr<ACollectedItem>> GetRandomList(int _sizeToList);
	void SetAllItemInList(TArray<TObjectPtr<ACollectedItem>> _allItem);
	void GenerateAndSetList(int Size);
};
