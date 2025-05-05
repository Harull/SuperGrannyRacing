#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "BoostingPill.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API ABoostingPill : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float boostTime = 5.0f;
	UPROPERTY(EditAnywhere) float boostRatio = 1.5f;
	
public:	
	ABoostingPill();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _target)override;

};
