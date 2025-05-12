// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Kart_HUD.h"

void AKart_HUD::BeginPlay()
{
	Super::BeginPlay();

	mainWidget = CreateWidget<UMainWidget>(GetWorld(), mainWidgetRef);
}

