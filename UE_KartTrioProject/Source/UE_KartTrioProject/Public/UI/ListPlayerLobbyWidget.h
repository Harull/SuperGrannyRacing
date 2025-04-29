// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ScrollBox.h>
#include "PlayerSlotLobbyWidget.h"
#include <Online/GIS_Online.h>
#include "ListPlayerLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API UListPlayerLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TSubclassOf<UPlayerSlotLobbyWidget> playerSlotRef;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UScrollBox> playerList;

private:
	void NativeConstruct() override;

public:
	void AddPlayer(FPlayerData _data);
};
