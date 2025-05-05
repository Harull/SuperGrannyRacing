// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollectedItemComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <GIS/GIS_CollectedItem.h>
#include <UI/Kart_HUD.h>
#include <SeniorPlayer.h>
#include "Components/PlaceArrowSignComponent.h"
#include "Components/BillboardComponent.h"
#include "Algo/Sort.h"
#include "Components/InventoryComponent.h"
#include <GIS/WS_PlayerClassement.h>

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
	UKismetSystemLibrary::PrintString(this, "Player List");


	TArray<TObjectPtr<UBillboardComponent>> _allBillboard = GetAllBillBoardComponents();
	for (UBillboardComponent* _billboardComponent : _allBillboard)
	{
		shoppingKartContentLocation.Add({ _billboardComponent, false });
	}


	UWS_PlayerClassement* _subPlayerClassement = GetWorld()->GetSubsystem<UWS_PlayerClassement>();
	if (_subPlayerClassement)
		_subPlayerClassement->AddPlayerCollectedItemComponent(this);

	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
	if (_sub)
	{
		if (_sub->GetRange() <= 0) return;
		_sub->GetRandomList(sizeList);
		_sub->SetAllItemInList();
		listItem = _sub->GetListItem();
	}

	if (listItem.Num() <= 0) return;
	seniorPlayerRef = Cast<ASeniorPlayer>(GetOwner());
	if (seniorPlayerRef->IsLocallyControlled())
		seniorPlayerRef->GetPlaceArrowSignComponent()->PlaceArrowNewPosition(GetCurrentItem()->GetItemPosition());
}

TArray<TObjectPtr<UBillboardComponent>> UCollectedItemComponent::GetAllBillBoardComponents()
{
	TArray<TObjectPtr<UBillboardComponent>> _result;

	TSet<UActorComponent*> _allActorComponent = GetOwner()->GetComponents();

	for (UActorComponent* _component : _allActorComponent)
	{
		if (UBillboardComponent* _billboardComponent = Cast<UBillboardComponent>(_component))
		{
			_result.Add(_billboardComponent);
		}
	}
	for (int _i = 0; _i < _result.Num() - 1; _i++)
	{
		int _minIndex = _i;
		for (int j = _i + 1; j < _result.Num(); j++)
		{
			if (_result[j]->GetName() < _result[_minIndex]->GetName())
			{
				_minIndex = j;
			}
		}

		if (_minIndex != _i)
		{
			_result.Swap(_i, _minIndex);
		}
	}
	
	UKismetSystemLibrary::PrintString(this, FString::FromInt(_result.Num()), true, true, FLinearColor::Red, 10.0f);
	return _result;
}

void UCollectedItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectedItemComponent::DestroyComponent(bool _bPromoteChildren)
{
	Super::DestroyComponent(_bPromoteChildren);
	UKismetSystemLibrary::PrintString(this, "Remove to subsystelm");
	UWS_PlayerClassement* _subPlayerClassement = GetWorld()->GetSubsystem<UWS_PlayerClassement>();
	if (_subPlayerClassement)
		_subPlayerClassement->RemovePlayerCollectedItemComponent(this);
}

//void UCollectedItemComponent::UseItem(const FInputActionValue& _valueFloat)
//{
//	if (!usableItem || isCooldown) return;
//	UKismetSystemLibrary::PrintString(this, "UseItem");
//	FVector _position = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * -100.0f;
//
//
//	if(!GetOwner()->HasAuthority())
//		SpawnItemServer(_position);
//	else
//		GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));
//
//	isCooldown = true;
//	FTimerHandle _timer;
//	GetWorld()->GetTimerManager().SetTimer(_timer, [&]() {UCollectedItemComponent::ResetCooldown(); }, timeCooldown, false);
//}

void UCollectedItemComponent::UpdateCurrentItem(TObjectPtr<ACollectedItem> _collectItem)
{
	//UKismetSystemLibrary::PrintString(this, "Hello1", true, true, FLinearColor::Blue, 10.0f);

	if (!_collectItem) return;
	//UKismetSystemLibrary::PrintString(this, "Hello2", true, true, FLinearColor::Blue, 10.0f);

	if (!seniorPlayerRef->IsLocallyControlled()) return;


	if (listItem.Num() == listItemCollected.Num()) return;
	if (listItem.Num() <= 0) return;

	//UKismetSystemLibrary::PrintString(this, "Hello3", true, true, FLinearColor::Blue, 10.0f);

	if (_collectItem == GetCurrentItem() && !listItemCollected.Contains(_collectItem))
	{
		nbItemCollected++;
		listItemCollected.Add(_collectItem);
		AddCollectedItemMeshToShoppingKart(_collectItem);

		if (listItem.Num() == listItemCollected.Num()) canFinish = true;

		if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			TObjectPtr<UItemToCollectWidget> _itemWidget = _hud->GetMainWidget()->FindItemWidget(_collectItem->GetItemName());
			if (_itemWidget)
				_itemWidget->CrossItem();
		}

		canFinish ? seniorPlayerRef->GetPlaceArrowSignComponent()->NoMoreItem()
			: seniorPlayerRef->GetPlaceArrowSignComponent()->PlaceArrowNewPosition(GetCurrentItem()->GetItemPosition());
	}
}

void UCollectedItemComponent::AddCollectedItemMeshToShoppingKart(TObjectPtr<ACollectedItem> _collectItem)
{
	int _meshIndex = GetAvailableShoppingKartPosition();
	UKismetSystemLibrary::PrintString(this, FString::FromInt(_meshIndex), true, true, FLinearColor::Blue, 10.0f);
	if (_meshIndex == -1) return;
	if (_collectItem->GetItemMesh())
	{
		ServerRPC_PlaceItemInShoppingCart(_collectItem, _meshIndex);
		PlaceItemInShoppingCart(_collectItem, _meshIndex);
	}
	seniorPlayerRef->GetInventoryComponent()->Reward();
}

int UCollectedItemComponent::GetAvailableShoppingKartPosition()
{
	// - 1 = not found
	for (int _i = 0; _i < shoppingKartContentLocation.Num(); _i++)
	{
		if (!shoppingKartContentLocation[_i].Value)
		{
			return _i;
		}
	}
	return -1;
}

void UCollectedItemComponent::ResetCooldown()
{
	isCooldown = false;
}

void UCollectedItemComponent::PlaceItemInShoppingCart(ACollectedItem* _collectItem, const int _meshIndex)
{
	// place mesh at a available place
	TObjectPtr<UStaticMeshComponent> _itemMesh = NewObject<UStaticMeshComponent>(this);
	_itemMesh->SetStaticMesh(_collectItem->GetItemMesh());
	_itemMesh->RegisterComponent();
	_itemMesh->AttachToComponent(shoppingKartContentLocation[_meshIndex].Key, FAttachmentTransformRules::SnapToTargetIncludingScale);
	_itemMesh->SetIsReplicated(true);

	shoppingKartContentLocation[_meshIndex].Value = true;
}

void UCollectedItemComponent::ServerRPC_PlaceItemInShoppingCart_Implementation(ACollectedItem* _collectItem, const int _meshIndex)
{
	PlaceItemInShoppingCart(_collectItem, _meshIndex);
}



//void UCollectedItemComponent::SpawnItemServer_Implementation(const FVector& _position)
//{
//	GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));
//}