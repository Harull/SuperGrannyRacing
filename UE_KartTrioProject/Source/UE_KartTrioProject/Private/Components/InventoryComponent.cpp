#include "Components/InventoryComponent.h"
#include "GPE/Item.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include "UI/MainWidget.h"
#include "UI/UsableItemWidget.h"
#include "UI/Kart_HUD.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateItemIcon();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> _item)
{
	if (items.Num() >= maxCount)return;
	items.Add(_item);
	UpdateItemIcon();
}

void UInventoryComponent::UseItem(const FInputActionValue& _value)
{
	if (items.IsEmpty())return;
	UKismetSystemLibrary::PrintString(this, "Use");

	if (items.IsEmpty() || !canUse)return;

	ASeniorPlayer* _owner = Cast<ASeniorPlayer>(GetOwner());
	if (!_owner)return;

	FVector _position = _owner->GetActorLocation() + _owner->GetActorForwardVector() * -150.0f;
	if (_owner->HasAuthority())
	{
		FActorSpawnParameters _spawnParams;
		_spawnParams.Owner = _owner;
		//_spawnParams.Instigator = Cast<APawn>(_owner);
		_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//FVector _position = _owner->GetActorLocation() + _owner->GetActorForwardVector() * -150.0f;
		FRotator _rotation = _owner->GetActorRotation();

		AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], _position, _rotation, _spawnParams);
		//AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], _position, _owner->GetActorRotation(), _spawnParams);

		if (_item)
		{
			UKismetSystemLibrary::PrintString(this, "Spawn");
			_item->Use(_owner);
		}

	}
	else
	{
		onUse.Broadcast(items[0], _owner, _position);
		//onUse.Broadcast(items[0], _owner->GetTransform());
	}

	items.RemoveAt(0);
	UpdateItemIcon();
}

UMainWidget* UInventoryComponent::GetMainWidget() const
{
	APlayerController* _playerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (!_playerController) return nullptr;

	AKart_HUD* _HUD = Cast< AKart_HUD>(_playerController->GetHUD());
	if (!_HUD)return nullptr;
	return _HUD->GetMainWidget();
}

void UInventoryComponent::UpdateItemIcon()
{
	UMainWidget* _mainWidget = GetMainWidget();
	if (!_mainWidget)return;
	UUsableItemWidget* _usableItemsWidget = _mainWidget->GetUsableItemWidget();
	if (!_usableItemsWidget)return;
	_usableItemsWidget->UpdateItemsImage(items);
}

