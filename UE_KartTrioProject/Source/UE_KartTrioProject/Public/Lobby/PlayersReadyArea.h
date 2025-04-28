
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <UI/Lobby_HUD.h>
#include <UI/LobbyWidget.h>
#include "PlayersReadyArea.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API APlayersReadyArea : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	
	UPROPERTY() TObjectPtr<ULobbyWidget> lobbyMenuRef = nullptr;

public:	
	APlayersReadyArea();

public:
	FORCEINLINE TObjectPtr<ULobbyWidget> GetLobbyMenuRef()
	{
		if (lobbyMenuRef)return lobbyMenuRef;
		if (ALobby_HUD* _hud = Cast<ALobby_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
			lobbyMenuRef = _hud->GetLobbyMenu();
		return lobbyMenuRef;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void OnOverlap(AActor* OtherActor);
	void OnEndOverlap(AActor* OtherActor);
};