#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootBoxSpawnPoint.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API ALootBoxSpawnPoint : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) bool isOccupied = false;

public:
	FORCEINLINE bool GetIsOccupied() { return isOccupied; }
	FORCEINLINE void SetIsOccupied(bool _isOccupied) {  isOccupied = _isOccupied; }
	
public:	
	ALootBoxSpawnPoint();

protected:
	virtual void BeginPlay() override;

private:
	void Init();

};
