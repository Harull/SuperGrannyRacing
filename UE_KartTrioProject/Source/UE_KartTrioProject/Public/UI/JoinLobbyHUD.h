// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SessionListWidget.h"
#include "JoinLobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API AJoinLobbyHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<USessionListWidget> lobbyMenuRef;
	UPROPERTY() TObjectPtr<USessionListWidget> lobbyMenu;

private:
	virtual void BeginPlay() override;
};
