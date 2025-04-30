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
	{
		UKismetSystemLibrary::PrintString(this, "Inventory Find", true, true, FLinearColor::Yellow, 5.0f);
		_inventory->OnUse().AddDynamic(this, &APC_SeniorPlayer::ServerRPC_SpawnActor);
	}
}

void APC_SeniorPlayer::ServerRPC_SpawnActor_Implementation(TSubclassOf<AItem> _item, ASeniorPlayer* _player, FVector _pos)
{
	if (!_player)return;
	UKismetSystemLibrary::PrintString(this, "ServerRPC_SpawnActor_Implementation", true, true, FLinearColor::Green, 5.0f);
	//AItem* _itemSpawn = GetWorld()->SpawnActor<AItem>(_item, _transform);
	AItem* _itemSpawn = GetWorld()->SpawnActor<AItem>(_item, _pos, _player->GetActorRotation());
	if (_itemSpawn)
	{
		UKismetSystemLibrary::PrintString(this, "ServerRPC_SpawnActor_Implementation => item spawn", true, true, FLinearColor::Green, 5.0f);
		_itemSpawn->Use(_player);
	}
}
