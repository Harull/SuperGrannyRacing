// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_KartBase.generated.h"

class ALootBox;
class ASeniorPlayer;

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API AGM_KartBase : public AGameModeBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TSubclassOf<ALootBox> lootBox;

protected:
	virtual void BeginPlay()override;
	
};
