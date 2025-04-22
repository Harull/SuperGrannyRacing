// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainWidget.h"
#include "Kart_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API AKart_HUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<UMainWidget> mainWidgetRef;
	UPROPERTY() TObjectPtr<UMainWidget> mainWidget;

public:
	FORCEINLINE TObjectPtr<UMainWidget> GetMainWidget() const { return mainWidget; }

private:
	virtual void BeginPlay() override;
};