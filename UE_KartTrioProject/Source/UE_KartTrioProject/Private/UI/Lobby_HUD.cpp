
#include "UI/Lobby_HUD.h"

void ALobby_HUD::BeginPlay()
{
	Super::BeginPlay();

	lobbyMenu = CreateWidget<USessionListWidget>(GetWorld(), lobbyMenuRef);
	lobbyMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
}
