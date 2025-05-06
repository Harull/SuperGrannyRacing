// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerSlotLobbyWidget.h"
#include <Kismet/KismetSystemLibrary.h>


void UPlayerSlotLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (GetOwningPlayer()->HasAuthority())
		Bind();
	else
		borderButton->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerSlotLobbyWidget::Bind()
{
	kickButton->OnClicked.AddDynamic(this, &UPlayerSlotLobbyWidget::KickPlayer);
}

void UPlayerSlotLobbyWidget::KickPlayer()
{
	UKismetSystemLibrary::PrintString(this, "Kick Button");
}

void UPlayerSlotLobbyWidget::Init(TObjectPtr<AActor> _playerRef, FString _name)
{
	playerRef = _playerRef;
	playerName->SetText(FText::FromString(_name));

	if (!_playerRef->HasAuthority())
		kickButton->SetVisibility(ESlateVisibility::Hidden);
}


