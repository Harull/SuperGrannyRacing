#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlaceArrowSignComponent.generated.h"

class AArrowSign;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API UPlaceArrowSignComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<AArrowSign> arrowToSpawn = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<AArrowSign> currentArrow = nullptr;

	UPROPERTY(EditAnywhere) float zOffset = 100.0f;

public:	
	UPlaceArrowSignComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void PlaceArrowNewPosition(const FVector& _targetPosition);
	void NoMoreItem();

private:
	void DestroyCurrentArrow();
};