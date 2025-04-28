// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "ReplicatedStartManager.generated.h"
UCLASS()
class UE_KARTTRIOPROJECT_API AReplicatedStartManager : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere) int playerCountToLookFor;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CurrentPlayerReady) int currentPlayerReady;

public:	
	AReplicatedStartManager();

protected:
	virtual void BeginPlay() override;
	void Debug();
private:
	void Init();
	void InitFields();
	
private:
	void ActivateAllPlayers();
	UFUNCTION() void OnRep_CurrentPlayerReady();

public:
	void IncrementCurrentPlayerReady();

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const;

};

