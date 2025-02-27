// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include <Kismet/KismetSystemLibrary.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BindButton();
}

void UMainMenuWidget::BindButton()
{

	playButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlay);
	quitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuit);
}

void UMainMenuWidget::OnPlay()
{
	UKismetSystemLibrary::PrintString(this, "PLAY");

	GetWorld()->ServerTravel("/Game/Levels/LVL_JoinLobby?listen");
}

void UMainMenuWidget::OnQuit()
{
	UKismetSystemLibrary::PrintString(this, "QUIT");
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}