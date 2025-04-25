// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/ReplicatedStartManager.h"
#include <Online/GIS_Online.h>
#include <Kismet/GameplayStatics.h>
#include <SeniorPlayer.h>

// Sets default values
AReplicatedStartManager::AReplicatedStartManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AReplicatedStartManager::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AReplicatedStartManager::Init()
{
	InitFields();
}

void AReplicatedStartManager::InitFields()
{
	playerCountToLookFor = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->GetNonSessionRelatedPlayerCount();
}

void AReplicatedStartManager::ActivateAllPlayers()
{
	TArray<AActor*> _outAllCharacters;
	UGameplayStatics::GetAllActorsOfClass(this, ASeniorPlayer::StaticClass(), _outAllCharacters);
	for (AActor* _actor : _outAllCharacters)
	{
		if (TObjectPtr<ASeniorPlayer> _senior = Cast<ASeniorPlayer>(_actor))
		{
			_senior->SetMovementActive(true); //TODO If have time, set a timer or start a countdown UI
		}
	}
}

void AReplicatedStartManager::OnRep_CurrentPlayerReady()
{
	if (playerCountToLookFor >= currentPlayerReady)
		ActivateAllPlayers();
}

void AReplicatedStartManager::Server_IncrementCurrentPlayerReady_Implementation()
{
	currentPlayerReady++;
}

void AReplicatedStartManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReplicatedStartManager, currentPlayerReady);
}
