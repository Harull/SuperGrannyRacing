
#include "Lobby/PlayersReadyArea.h"
#include <UI/Lobby_HUD.h>
#include <Kismet/KismetSystemLibrary.h>

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

	FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
		if (ALobby_HUD* _hud = Cast<ALobby_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			UKismetSystemLibrary::PrintString(this, "Find HUD");

			if (lobbyMenuRef = _hud->GetLobbyMenu())
			{
				UKismetSystemLibrary::PrintString(this, "Find widget");
			}
			else
			{
				UKismetSystemLibrary::PrintString(this, "Didnt find widget");
			}
		}
		else
		{
			UKismetSystemLibrary::PrintString(this, "Didnt find HUD");
		}
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 2.0f, false, 2.0f);
	
}

void APlayersReadyArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayersReadyArea::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UKismetSystemLibrary::PrintString(this, "Enter");

	lobbyMenuRef->UpdatePlayersReady(1);
}

void APlayersReadyArea::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	UKismetSystemLibrary::PrintString(this, "Exit");
	lobbyMenuRef->UpdatePlayersReady(-1);
}