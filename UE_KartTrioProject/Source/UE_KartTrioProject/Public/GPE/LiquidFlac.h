#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "LiquidFlac.generated.h"

class ASeniorPlayer;

USTRUCT()
struct FSlipperySettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float slipTime = 2.f;
	UPROPERTY(EditAnywhere) float slipSpeed = 70.f; //TODO lerp the slipping speed from max to 0, based on the time slipping (max/current)
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 1, UImin = 0, UImax = 1)) float losingControlOverSteeringRation = 0.7f;

};

UCLASS()
class UE_KARTTRIOPROJECT_API ALiquidFlac : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) FSlipperySettings slipSettings;
	
public:	
	ALiquidFlac();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _player)override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
