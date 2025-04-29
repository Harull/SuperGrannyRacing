#include "PC_SeniorPlayer.h"
#include "SeniorPlayer.h"
#include "GPE/Item.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/InventoryComponent.h"

void APC_SeniorPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerSenior = Cast<ASeniorPlayer>(GetPawn());
	if (!playerSenior)return;

	UKismetSystemLibrary::PrintString(this, "Bind");

	UInventoryComponent* _inventory = playerSenior->GetInventoryComponent();
	if (_inventory)
		_inventory->OnUse().AddDynamic(this, &APC_SeniorPlayer::ServerRPC_SpawnActor);
}

void APC_SeniorPlayer::ServerRPC_SpawnActor_Implementation(TSubclassOf<AItem> _item, ASeniorPlayer* _player)
{
	AItem* _itemSpawn = GetWorld()->SpawnActor<AItem>(_item, _player->GetTransform());
	if (_itemSpawn)
		_itemSpawn->Use(_player);
}
