#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ULootBoxSpawnPointSubsystem.generated.h"

class ALootBoxSpawnPoint;
class ALootBox;


UCLASS()
class UE_KARTTRIOPROJECT_API UULootBoxSpawnPointSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)TSubclassOf<ALootBox> lootBoxToSpawn;
	TArray<TObjectPtr<ALootBoxSpawnPoint>> allSpawnPoints;
	float time = 5.0f;

public:
	void RegisterSpawnPoint(ALootBoxSpawnPoint* _spawnPoint);
	void LootBoxCollected();
	void SetLootBoxToSpawn(TSubclassOf<ALootBox> _lootBox);

private:
	void RespawnLootBox();
	
};
