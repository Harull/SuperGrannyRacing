// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinLobbyHUD.h"

void AJoinLobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	lobbyMenu = CreateWidget<USessionListWidget>(GetWorld(), lobbyMenuRef);
	lobbyMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
}