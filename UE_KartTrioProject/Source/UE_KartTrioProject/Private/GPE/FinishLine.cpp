// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/FinishLine.h"
#include "Components/BillboardComponent.h"
#include <SeniorPlayer.h>
#include <Components/CollectedItemComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <UI/Kart_HUD.h>


// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	//billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	box = CreateDefaultSubobject<UBoxComponent>("Box");

	//billboard->SetupAttachment(RootComponent);
	box->SetupAttachment(RootComponent);

	bReplicates = true;
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLine::NotifyActorBeginOverlap(AActor* _otherActor)
{
	ASeniorPlayer* _player = Cast<ASeniorPlayer>(_otherActor);
	if (!_player) return;
	//UCollectedItemComponent* _comp =  _player->GetComponentByClass<UCollectedItemComponent>();
	UCollectedItemComponent* _comp =  _player->GetCollectedItemComponent();
	if (!_comp) return;
	
	if (_comp->CanFinish())
	{
		_comp->SetHasFinish(true);
		RegisterPlayerFinish(_player);
		int _rank = GetPlayerRank(_player);

		FString _rankStr = FString::Printf(TEXT("You finished %d%s!"), _rank, *GetOrdinalSuffix(_rank));

		UKismetSystemLibrary::PrintString(this, "Finish");
		if(APlayerController* _controller = Cast<APlayerController>(_player->GetController()))
		{
			if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(_controller->GetHUD()))
			{
				UKismetSystemLibrary::PrintString(this, "Affiche WIN");
				_hud->GetMainWidget()->SetWinScreenVisibility();
				_hud->GetMainWidget()->GetWinScreenWidget()->SetText(FText::FromString(_rankStr));
				if(_hud->GetMainWidget()->GetUsableSpecialItemWidget()->GetVisibility() == ESlateVisibility::Visible)
					_hud->GetMainWidget()->GetUsableSpecialItemWidget()->SetVisibility(ESlateVisibility::Hidden);
			}
			_player->DisableInput(_controller);
			_player->SetActorEnableCollision(false);
		}
		onStopRace.Broadcast();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "NO Finish");
	}
}

FString AFinishLine::GetOrdinalSuffix(int _number)
{
	int _tens = _number % 100;
	int _unit = _number % 10;

	if (_tens >= 11 && _tens <= 13)
		return "th";

	switch (_unit)
	{
	case 1: 
		return "st";
	case 2:
		return "nd";
	case 3: 
		return "rd";
	default: 
		return "th";
	}
}

void AFinishLine::RegisterPlayerFinish(ASeniorPlayer* _player)
{
	//if (!HasAuthority()) return;

	/*if (!playerPlacements.Contains(_player))
	{*/
		playerFinishCount++;
		//playerPlacements.Add(_player, playerFinishCount);
	//}
}

int AFinishLine::GetPlayerRank(ASeniorPlayer* _player)
{
	/*if (playerPlacements.Contains(_player))
	{
		return playerPlacements[_player];
	}
	return -1;*/
	return playerFinishCount;
}

void AFinishLine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFinishLine, playerFinishCount);
}



