// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollectedItemComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <GIS/GIS_CollectedItem.h>
#include <UI/Kart_HUD.h>
#include <SeniorPlayer.h>
#include "Components/PlaceArrowSignComponent.h"
#include "Components/DestinationArrowComponent.h"
#include "GPE/DestinationArrow.h"
#include "Components/BillboardComponent.h"
#include "Algo/Sort.h"
#include "Components/InventoryComponent.h"
#include <GIS/WS_PlayerClassement.h>
#include "GPE/Item.h"

// Sets default values for this component's properties
UCollectedItemComponent::UCollectedItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UCollectedItemComponent::BeginPlay()
{
	Super::BeginPlay();

	seniorPlayerRef = Cast<ASeniorPlayer>(GetOwner());
	if (!seniorPlayerRef)
		return;

	TArray<TObjectPtr<UBillboardComponent>> _allBillboards = GetAllBillBoardComponents();
	for (UBillboardComponent* _billboardComp : _allBillboards)
	{
		shoppingKartContentLocation.Add({ _billboardComp, false });
	}

	if (UWS_PlayerClassement* _subPlayerClassement = GetWorld()->GetSubsystem<UWS_PlayerClassement>())
	{
		_subPlayerClassement->AddPlayerCollectedItemComponent(this);
	}

	if (GetOwner()->HasAuthority())
	{
		FTimerHandle _timer;
		//GetWorld()->GetTimerManager().SetTimer(_timer, [this]() {
		if (UGIS_CollectedItem* _subsys = GetWorld()->GetSubsystem<UGIS_CollectedItem>())
		{
			listItem = _subsys->GetRandomList(6);
			OnRep_ListItem();
		}
		//}, 1.0f, false);
	}

	if (listItem.Num() <= 0) return;

	if (seniorPlayerRef->IsLocallyControlled())
	{
		if (TObjectPtr<UPlaceArrowSignComponent> _arrowComp = seniorPlayerRef->GetPlaceArrowSignComponent())
		{
			_arrowComp->PlaceArrowNewPosition(GetCurrentItem()->GetItemPosition());

			FTimerHandle _timer;
			GetWorld()->GetTimerManager().SetTimer(_timer, [&]()
				{
					if (TObjectPtr<ADestinationArrow> _arrow = seniorPlayerRef->GetDestinationArrowComponent()->GetCurrentArrow())
					{
						_arrow->SetTarget(GetCurrentItem()->GetItemPosition());
						UKismetSystemLibrary::PrintString(this, "Salut la team", true, true, FLinearColor::Red, 20.0f);
					}
				}, 1, false);
		}
	}
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
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(listItem.Num()), true, true, FLinearColor::Red, 1);

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

void UCollectedItemComponent::UpdateCurrentItem(TObjectPtr<ACollectedItem> _collectItem/*, TSubclassOf<AItem> _givenItem*/)
{
	//UKismetSystemLibrary::PrintString(this, "Hello1", true, true, FLinearColor::Blue, 10.0f);

	if (!_collectItem) return;
	//UKismetSystemLibrary::PrintString(this, "Hello2", true, true, FLinearColor::Blue, 10.0f);

	if (!seniorPlayerRef) return;
	if (!seniorPlayerRef->IsLocallyControlled()) return;


	if (listItem.Num() == listItemCollected.Num()) return;
	if (listItem.Num() <= 0) return;

	//UKismetSystemLibrary::PrintString(this, "Hello3", true, true, FLinearColor::Blue, 10.0f);

	if (_collectItem == GetCurrentItem() && !listItemCollected.Contains(_collectItem))
	{
		nbItemCollected++;
		listItemCollected.Add(_collectItem);
		AddCollectedItemMeshToShoppingKart(_collectItem/*, _givenItem*/);
		if (listItem.Num() == listItemCollected.Num()) canFinish = true;


		if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			TObjectPtr<UItemToCollectWidget> _itemWidget = _hud->GetMainWidget()->FindItemWidget(_collectItem->GetItemName());
			if (_itemWidget)
				_itemWidget->CrossItem();
		}
		TObjectPtr<ADestinationArrow> _arrow = seniorPlayerRef->GetDestinationArrowComponent()->GetCurrentArrow();
		if (canFinish)
		{
			seniorPlayerRef->GetPlaceArrowSignComponent()->NoMoreItem();
			if (_arrow)
				_arrow->SetTarget(FVector::ZeroVector);
		}
		else
		{
			seniorPlayerRef->GetPlaceArrowSignComponent()->PlaceArrowNewPosition(GetCurrentItem()->GetItemPosition());
			if (_arrow)
				_arrow->SetTarget(GetCurrentItem()->GetItemPosition());
		}
		if (_arrow)
			_arrow->SetShoppingListCompleted(AreAllItemsCollected());
	}
}

void UCollectedItemComponent::AddCollectedItemMeshToShoppingKart(TObjectPtr<ACollectedItem> _collectItem/*, TSubclassOf<AItem> _givenItem*/)
{
	int _meshIndex = GetAvailableShoppingKartPosition();
	UKismetSystemLibrary::PrintString(this, FString::FromInt(_meshIndex), true, true, FLinearColor::Blue, 10.0f);
	if (_meshIndex == -1) return;
	if (_collectItem->GetItemMesh())
	{
		ServerRPC_PlaceItemInShoppingCart(_collectItem, _meshIndex);
		PlaceItemInShoppingCart(_collectItem, _meshIndex);
	}
	seniorPlayerRef->GetInventoryComponent()->Reward(/*_givenItem*/);
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



void UCollectedItemComponent::OnRep_ListItem()
{
	FString _role = GetOwner()->HasAuthority() ? "Server" : "Client";
	UKismetSystemLibrary::PrintString(this, "OnRep_ListItem() fired on" + _role + " " + FString::FromInt(listItem.Num()), true, true, FLinearColor::Red, 20);

	if (TObjectPtr<AKart_HUD> _hud = Cast<AKart_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		TObjectPtr<UMainWidget> _mainWidget = _hud->GetMainWidget();
		if (_mainWidget)
		{
			UKismetSystemLibrary::PrintString(this, "InitShoppingList", true, true, FLinearColor::Red, 20);
			_mainWidget->InitShoppingList(listItem);
		}
	}
}


void UCollectedItemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCollectedItemComponent, listItem);
}

//void UCollectedItemComponent::ReceiveShoppingListFromServer(const TArray<ACollectedItem*>& _sharedList)
//{
//	UKismetSystemLibrary::PrintString(this, "ClientRPC_ReceiveShoppingList", true, true, FLinearColor::Red, 20);
//	listItem = _sharedList;
//	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
//	if (_sub)
//	{
//		_sub->SetAllItemInList(listItem);
//	}
//}

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