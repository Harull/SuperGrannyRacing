#include "Components/InventoryComponent.h"
#include "GPE/Item.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> _item)
{
	if (items.Num() >= maxCount)return;
	items.Add(_item);
}

void UInventoryComponent::UseItem(const FInputActionValue& _value)
{
	if (items.IsEmpty())return;
	UKismetSystemLibrary::PrintString(this, "Use");

	if (items.IsEmpty() || !canUse)return;

	ASeniorPlayer* _owner = Cast<ASeniorPlayer>(GetOwner());
	if (!_owner)return;

	if (_owner->HasAuthority())
	{
		FActorSpawnParameters _spawnParams;
		_spawnParams.Owner = _owner;
		//_spawnParams.Instigator = Cast<APawn>(_owner);
		_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector _position = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * -100.0f;

		AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], _position, FRotator(0), _spawnParams);
		//AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], _position, _owner->GetActorRotation(), _spawnParams);

		if (_item)
		{
			UKismetSystemLibrary::PrintString(this, "Spawn");
			_item->Use(_owner);
		}

	}
	else
	{
		onUse.Broadcast(items[0], _owner);
	}

	items.RemoveAt(0);
}

