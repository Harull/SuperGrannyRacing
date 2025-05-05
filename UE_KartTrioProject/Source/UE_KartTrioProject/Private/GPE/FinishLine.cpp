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
		UKismetSystemLibrary::PrintString(this, "Finish");
		if(APlayerController* _controller = Cast<APlayerController>(_player->GetController()))
		{
			if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(_controller->GetHUD()))
			{
				UKismetSystemLibrary::PrintString(this, "Affiche WIN");
				_hud->GetMainWidget()->SetWinScreenVisibility();
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

