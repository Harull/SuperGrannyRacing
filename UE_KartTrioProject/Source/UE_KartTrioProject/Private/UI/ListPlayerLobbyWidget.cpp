// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ListPlayerLobbyWidget.h"
#include <GIS/WS_PlayerClassement.h>

void UListPlayerLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UListPlayerLobbyWidget::ClearChildrens()
{
	playerList->ClearChildren();
}

void UListPlayerLobbyWidget::AddPlayer(TObjectPtr<AActor> _playerRef, FString _name)
{
	TObjectPtr<UPlayerSlotLobbyWidget> _playerSlot = CreateWidget<UPlayerSlotLobbyWidget>(GetWorld(), playerSlotRef);
	_playerSlot->Init(_playerRef, _name);
	playerList->AddChild(_playerSlot);
}
