
#include "Lobby/PlayersReadyArea.h"
#include <Kismet/KismetSystemLibrary.h>
#include <SeniorPlayer.h>

APlayersReadyArea::APlayersReadyArea()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void APlayersReadyArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayersReadyArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayersReadyArea::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//UKismetSystemLibrary::PrintString(this, "Enter");
	OnOverlap(OtherActor);
}

void APlayersReadyArea::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	//UKismetSystemLibrary::PrintString(this, "Exit");
	OnEndOverlap(OtherActor);

}

void APlayersReadyArea::OnOverlap(AActor* OtherActor)
{
	if(ASeniorPlayer * _player = Cast<ASeniorPlayer>(OtherActor))
	{
		if (GetLobbyMenuRef())
			lobbyMenuRef->UpdatePlayersReady(1);
		else
		{
			FTimerHandle _timer;
			FTimerDelegate _delegate;
			_delegate.BindLambda([&]() {
				OnOverlap(OtherActor);
				});
			GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, .1f, false, .1f);
		}
	}
}

void APlayersReadyArea::OnEndOverlap(AActor* OtherActor)
{
	if (ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor))
	{
		if (GetLobbyMenuRef())
			lobbyMenuRef->UpdatePlayersReady(-1);
		else
		{
			FTimerHandle _timer;
			FTimerDelegate _delegate;
			_delegate.BindLambda([&]() {
				OnEndOverlap(OtherActor);
				});
			GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, .1f, false, .1f);
		}
	}
}
