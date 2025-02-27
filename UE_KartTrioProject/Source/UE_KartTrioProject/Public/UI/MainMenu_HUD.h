// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
#include "MainMenu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API AMainMenu_HUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<UMainMenuWidget> mainMenuRef;
	UPROPERTY() TObjectPtr<UMainMenuWidget> mainMenu;

private:
	virtual void BeginPlay() override;

};
