// Fill out your copyright notice in the Description page of Project Settings.


#include "GIS/WS_PlayerClassement.h"
#include <UI/Lobby_HUD.h>
#include <SeniorPlayer.h>

void UWS_PlayerClassement::AddPlayerInMap(TObjectPtr<AActor> _actor, FString _playerName)
{
	/*
	if (allPlayer.Contains(_actor)) return;
	allPlayer.Add(_actor, _playerName);
	AHUD* _hud = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetHUD();

	if (ALobby_HUD* _newHUD = Cast<ALobby_HUD>(_hud))
	{
		_newHUD->GetLobbyMenu()->GetListPlayerLobbyWidget()->AddPlayer(_actor, _playerName);
	}
	*/
}

void UWS_PlayerClassement::AddPlayerCollectedItemComponent(TObjectPtr<UCollectedItemComponent> _playerCollectedItemComponent)
{
	if (!_playerCollectedItemComponent || allPlayerCollectedItemComponent.Contains(_playerCollectedItemComponent)) return;
	allPlayerCollectedItemComponent.Add(_playerCollectedItemComponent);
}

void UWS_PlayerClassement::RemovePlayerCollectedItemComponent(TObjectPtr<UCollectedItemComponent> _playerCollectedItemComponent)
{
	if (!_playerCollectedItemComponent || !allPlayerCollectedItemComponent.Contains(_playerCollectedItemComponent)) return;
	allPlayerCollectedItemComponent.Remove(_playerCollectedItemComponent);
}

TArray<TObjectPtr<UCollectedItemComponent>> UWS_PlayerClassement::UpdatePlayerClassement()
{
	if (allPlayerCollectedItemComponent.Num() <= 1) return {};
	TArray<TObjectPtr<UCollectedItemComponent>> _refList = allPlayerCollectedItemComponent;
	TArray<TObjectPtr<UCollectedItemComponent>> _newList = {};
	int _size = _refList.Num();
	int _currentPos = _refList[0]->GetSizeList();

	while (_newList.Num() < _size || _currentPos < 0)
	{
		UCollectedItemComponent* _playerToRemove = nullptr;
		for (UCollectedItemComponent* _player : _refList)
		{
			int _newNum = _player->GetNumItemCollected();
			if (_newNum == _currentPos)
			{
				_newList.Add(_player);
				_playerToRemove = _player;
				continue;
			}
			else
			{
				_currentPos--;
			}
		}
		_refList.Remove(_playerToRemove);
	}

	return _newList;
}