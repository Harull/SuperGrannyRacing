#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_SeniorPlayer.generated.h"

class ASeniorPlayer;
class AItem;

UCLASS()
class UE_KARTTRIOPROJECT_API APC_SeniorPlayer : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<ASeniorPlayer> playerSenior;
private:
	virtual void BeginPlay()override;
	UFUNCTION(Server, Reliable) void ServerRPC_SpawnActor(TSubclassOf<AItem> _item, ASeniorPlayer* _player);
	
};
