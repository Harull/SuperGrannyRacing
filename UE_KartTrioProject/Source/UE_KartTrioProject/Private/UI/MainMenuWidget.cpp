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

	//abonnement bouton back du session list widget a faire 
}

void UMainMenuWidget::OnPlay()
{
	UKismetSystemLibrary::PrintString(this, "PLAY");

	//GetWorld()->ServerTravel("/Game/Levels/LVL_JoinLobby?listen");
	//Hide MainMenu
	//Show JoinLobby

	mainMenuLayout->SetVisibility(ESlateVisibility::Hidden);
	sessionListLayout->SetVisibility(ESlateVisibility::Visible);
	sessionListLayout->SetIsEnabled(true);
	sessionListLayout->FindSessions();
}

void UMainMenuWidget::OnQuit()
{
	UKismetSystemLibrary::PrintString(this, "QUIT");
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}