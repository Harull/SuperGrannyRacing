#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "FlashLight.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API AFlashLight : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float time = 3.0f;
	UPROPERTY(EditDefaultsOnly) UMaterialInterface* malusMaterial;
	
public:	
	AFlashLight();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _target)override;

};
