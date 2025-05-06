
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyWidget.h"
#include "Lobby_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API ALobby_HUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<ULobbyWidget> lobbyMenuRef;
	UPROPERTY() TObjectPtr<ULobbyWidget> lobbyMenu;

public:
	FORCEINLINE TObjectPtr<ULobbyWidget> GetLobbyMenu() const { return lobbyMenu; }
	void TogglePlayerList();

private:
	virtual void BeginPlay() override;
};
