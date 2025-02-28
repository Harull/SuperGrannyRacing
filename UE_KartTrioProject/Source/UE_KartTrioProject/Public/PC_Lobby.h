
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Lobby.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API APC_Lobby : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;
};
