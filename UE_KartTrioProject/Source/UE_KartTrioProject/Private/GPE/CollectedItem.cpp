
// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/CollectedItem.h"

ACollectedItem::ACollectedItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACollectedItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACollectedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
