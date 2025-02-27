
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SessionListWidget.h"
#include "Lobby_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API ALobby_HUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<USessionListWidget> lobbyMenuRef;
	UPROPERTY() TObjectPtr<USessionListWidget> lobbyMenu;

private:
	virtual void BeginPlay() override;
};
