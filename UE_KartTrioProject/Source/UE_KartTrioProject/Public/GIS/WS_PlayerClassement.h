// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <Components/CollectedItemComponent.h>
#include "WS_PlayerClassement.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UWS_PlayerClassement : public UWorldSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<UCollectedItemComponent>> allPlayerCollectedItemComponent;

public:
	FORCEINLINE TArray<TObjectPtr<UCollectedItemComponent>> GetAllPlayerCollectedItemComponent() const { return allPlayerCollectedItemComponent; }
	FORCEINLINE int GetRange() const { return allPlayerCollectedItemComponent.Num(); }
public:
	void AddPlayerInMap(TObjectPtr<AActor> _actor, FString _playerName);
	void AddPlayerCollectedItemComponent(TObjectPtr<UCollectedItemComponent> _playerCollectedItemComponent);
	void RemovePlayerCollectedItemComponent(TObjectPtr<UCollectedItemComponent> _playerCollectedItemComponent);
	TArray<TObjectPtr<UCollectedItemComponent>> UpdatePlayerClassement();
	void CheckIsPlayerIsNull();

};