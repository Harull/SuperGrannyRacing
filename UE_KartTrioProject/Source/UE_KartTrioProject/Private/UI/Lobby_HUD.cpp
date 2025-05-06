
#include "UI/Lobby_HUD.h"


void ALobby_HUD::BeginPlay()
{
	Super::BeginPlay();

	lobbyMenu = CreateWidget<ULobbyWidget>(GetWorld(), lobbyMenuRef);
	lobbyMenu->AddToViewport();

	GetOwningPlayerController()->SetShowMouseCursor(true);
}

void ALobby_HUD::TogglePlayerList()
{
	lobbyMenu->TogglePlayerList();
}