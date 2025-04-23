// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollectedItemComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <GIS/GIS_CollectedItem.h>
#include <UI/Kart_HUD.h>

// Sets default values for this component's properties
UCollectedItemComponent::UCollectedItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollectedItemComponent::BeginPlay()
{
	Super::BeginPlay();

	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
	if (_sub)
		listItem = _sub->GetListCollectedItem();
	// ...
	
}


// Called every frame
void UCollectedItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollectedItemComponent::UseItem(const FInputActionValue& _valueFloat)
{
	if (!usableItem || isCooldown) return;
	UKismetSystemLibrary::PrintString(this, "UseItem");
	FVector _position = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * -100.0f;


	if(!GetOwner()->HasAuthority())
		SpawnItemServer(_position);
	else
		GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));

	isCooldown = true;
	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, [&]() {UCollectedItemComponent::ResetCooldown(); }, timeCooldown, false);
}

void UCollectedItemComponent::UpdateCurrentItem(TObjectPtr<ACollectedItem> _collectItem)
{
	if (!_collectItem)
	{
		UKismetSystemLibrary::PrintString(this, "No CollectItem");
		return;
	}
	if (listItem.Num() == listItemCollected.Num()) return;
	if(listItem.Num() <= 0)
		UKismetSystemLibrary::PrintString(this, "Liste de merde a zero");

	if (_collectItem == GetCurrentItem() && !listItemCollected.Contains(_collectItem))
	{
		//UKismetSystemLibrary::PrintString(this, "Truc de merde recuperer !!");
		_collectItem->GetItemName();
		nbItemCollected++;
		listItemCollected.Add(_collectItem);

		if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			TObjectPtr<UItemToCollectWidget> _itemWidget = _hud->GetMainWidget()->FindItemWidget(_collectItem->GetItemName());
			_itemWidget->CrossItem();
		}

		if (listItem.Num() == listItemCollected.Num()) canFinish = true;
	}
}

void UCollectedItemComponent::ResetCooldown()
{
	isCooldown = false;
}

void UCollectedItemComponent::SpawnItemServer_Implementation(const FVector& _position)
{
	GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));
}