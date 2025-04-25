// Fill out your copyright notice in the Description page of Project Settings.


#include "GIS/WS_PlayerClassement.h"

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

int UWS_PlayerClassement::GetPlayerClassement(TObjectPtr<UCollectedItemComponent> _playerCollectedItemComponent)
{
	if (!_playerCollectedItemComponent) return -1;

	int _size = allPlayerCollectedItemComponent.Num();
	
	for (size_t i = 1; i < _size +1; i++)
	{
		if (allPlayerCollectedItemComponent[i] == _playerCollectedItemComponent) return i;
	}

	return -1;
}
