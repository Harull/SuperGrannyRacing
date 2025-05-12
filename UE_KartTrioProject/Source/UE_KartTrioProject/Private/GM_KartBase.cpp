// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_KartBase.h"
#include "GPE/LootBox.h"
#include "GIS/GIS_CollectedItem.h"
#include "GPE/ULootBoxSpawnPointSubsystem.h"
#include <SeniorPlayer.h>

void AGM_KartBase::BeginPlay()
{
	Super::BeginPlay();

	if (UULootBoxSpawnPointSubsystem* _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UULootBoxSpawnPointSubsystem>())
		_subsystem->SetLootBoxToSpawn(lootBox);


	UGIS_CollectedItem* _subsystem = GetWorld()->GetSubsystem<UGIS_CollectedItem>();
	if (_subsystem && _subsystem->ItemListIsEmpty())
	{
		_subsystem->GenerateAndSetList(sizeList);
	}
}

