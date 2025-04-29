// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "PlayerSlotLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UPlayerSlotLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> playerName;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> kickButton;
};
