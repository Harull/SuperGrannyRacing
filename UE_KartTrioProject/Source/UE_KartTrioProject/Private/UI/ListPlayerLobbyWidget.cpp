// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ListPlayerLobbyWidget.h"
#include <GIS/WS_PlayerClassement.h>

void UListPlayerLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UListPlayerLobbyWidget::AddPlayer(FPlayerData _data)
{
	TObjectPtr<UPlayerSlotLobbyWidget> _playerSlot = CreateWidget<UPlayerSlotLobbyWidget>(GetWorld(), playerSlotRef);
	_playerSlot->SetPlayerData(_data);
	playerList->AddChild(_playerSlot);
}
