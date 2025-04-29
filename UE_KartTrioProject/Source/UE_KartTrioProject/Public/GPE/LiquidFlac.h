#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "LiquidFlac.generated.h"

class ASeniorPlayer;

UCLASS()
class UE_KARTTRIOPROJECT_API ALiquidFlac : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float stunTime = 2.0f;
	
public:	
	ALiquidFlac();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _player)override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
