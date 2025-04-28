#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "ToiletPaper.generated.h"

class ASeniorPlayer;

UCLASS()
class UE_KARTTRIOPROJECT_API AToiletPaper : public AItem
{
	GENERATED_BODY()
	
public:	
	AToiletPaper();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _player)override;

};
