#include "GPE/ULootBoxSpawnPointSubsystem.h"
#include "GPE/LootBoxSpawnPoint.h"
#include "GPE/LootBox.h"
#include <Kismet/KismetSystemLibrary.h>

void UULootBoxSpawnPointSubsystem::RegisterSpawnPoint(ALootBoxSpawnPoint* _spawnPoint)
{
	if (!_spawnPoint)return;
	allSpawnPoints.Add(_spawnPoint);
}

void UULootBoxSpawnPointSubsystem::LootBoxCollected()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			FTimerHandle _timer;
			GetWorld()->GetTimerManager().SetTimer(_timer, this, &UULootBoxSpawnPointSubsystem::RespawnLootBox, time, false);
		});
}

void UULootBoxSpawnPointSubsystem::SetLootBoxToSpawn(TSubclassOf<ALootBox> _lootBox)
{
	lootBoxToSpawn = _lootBox;
}

void UULootBoxSpawnPointSubsystem::RespawnLootBox()
{
	if (allSpawnPoints.Num() == 0 || !lootBoxToSpawn) return;
	UKismetSystemLibrary::PrintString(this, "Call");

	TArray<ALootBoxSpawnPoint*> _freeSpawnPoints;
	for (ALootBoxSpawnPoint* _spawn : allSpawnPoints)
	{
		if (_spawn && !_spawn->GetIsOccupied())
		{
			_freeSpawnPoints.Add(_spawn);
		}
	}

	if (_freeSpawnPoints.Num() == 0) return;
	UKismetSystemLibrary::PrintString(this, "Free");
	int _count = _freeSpawnPoints.Num() - 1;

	int _randIndex = FMath::RandRange(0, _count);
	ALootBoxSpawnPoint* _chosenSpawn = _freeSpawnPoints[_randIndex];

	if (!_chosenSpawn) return;

	UWorld* _world = GetWorld();
	if (_world && _world->GetNetMode() != NM_Client)
	{
		FActorSpawnParameters _params;
		_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ALootBox* _lootBox = _world->SpawnActor< ALootBox>(lootBoxToSpawn, _chosenSpawn->GetActorTransform(), _params);

		if (_lootBox)
		{
			UKismetSystemLibrary::PrintString(this, "Spawn");
			_chosenSpawn->SetIsOccupied(true);
			_lootBox->SetOwningSpawnPoint(_chosenSpawn);
		}
			
	}

}
