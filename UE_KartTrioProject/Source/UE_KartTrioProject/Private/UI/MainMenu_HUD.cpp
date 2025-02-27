// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu_HUD.h"

void AMainMenu_HUD::BeginPlay()
{
	Super::BeginPlay();

	mainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), mainMenuRef);
	mainMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
}
