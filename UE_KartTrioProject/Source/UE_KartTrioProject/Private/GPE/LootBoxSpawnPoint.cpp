#include "GPE/LootBoxSpawnPoint.h"
#include "GPE/ULootBoxSpawnPointSubsystem.h"

ALootBoxSpawnPoint::ALootBoxSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALootBoxSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void ALootBoxSpawnPoint::Init()
{
	UULootBoxSpawnPointSubsystem* _subsystem = GetWorld()->GetGameInstance()->GetSubsystem< UULootBoxSpawnPointSubsystem>();
	if (!_subsystem)return;

	_subsystem->RegisterSpawnPoint(this);
}
