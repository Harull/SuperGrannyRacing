// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Border.h>
#include <Online/GIS_Online.h>
#include "PlayerSlotLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UPlayerSlotLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY() TObjectPtr<AActor> playerRef;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> playerName;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UBorder> borderButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> kickButton;

private:
	virtual void NativeConstruct() override;
	void Bind();

	UFUNCTION() void KickPlayer();

public:
	void Init(TObjectPtr<AActor> _playerRef, FString _name);
};
