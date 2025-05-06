#include "Components/InventoryComponent.h"
#include "GPE/Item.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include "UI/MainWidget.h"
#include "UI/UsableItemWidget.h"
#include "UI/ObtainItemWidget.h"
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

	//ToggleText();
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

void UInventoryComponent::UseSpecialItem(const FInputActionValue& _value)
{
	if (!canUseSpecialItem || ! specialItem)return;

	ASeniorPlayer* _owner = Cast<ASeniorPlayer>(GetOwner());
	if (!_owner)return;

	FVector _position = _owner->GetActorLocation() + _owner->GetActorForwardVector() * -150.0f;
	if (_owner->HasAuthority())
	{
		FActorSpawnParameters _spawnParams;
		_spawnParams.Owner = _owner;
		_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FRotator _rotation = _owner->GetActorRotation();

		AItem* _item = GetWorld()->SpawnActor<AItem>(specialItem, _position, _rotation, _spawnParams);

		if (_item)
		{
			_item->Use(_owner);
		}

	}
	else
	{
		onUse.Broadcast(specialItem, _owner, _position);
	}

	canUseSpecialItem = false;
	GetMainWidget()->GetUsableSpecialItemWidget()->SetVisibility(ESlateVisibility::Hidden);
	onStartAnim.Broadcast();
	UKismetSystemLibrary::PrintString(this, "Start Anim");

}

void UInventoryComponent::Reward()
{
	if (rewardItems.IsEmpty())return;
	int _count = rewardItems.Num() - 1;
	int _rand = FMath::RandRange(0,_count);
	TSubclassOf<AItem> _rewardItem = rewardItems[_rand];
	AddItem(_rewardItem);

	ToggleText();
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

void UInventoryComponent::ToggleText()
{
	UObtainItemWidget* _obtainItemWidget = GetMainWidget()->GetObtainItemWidget();
	_obtainItemWidget->SetVisibility(ESlateVisibility::Visible);

	TWeakObjectPtr<UObtainItemWidget> _weakWidget = _obtainItemWidget;

	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, [_weakWidget]()
		{
			if (_weakWidget.IsValid())
			{
				_weakWidget->SetVisibility(ESlateVisibility::Hidden);
			}


		}, 2.0f, false);
}

