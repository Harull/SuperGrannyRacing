// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GPE/CollectedItem.h>
#include "CollectedItemComponent.generated.h"

class ASeniorPlayer;
class UBillboardComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE_KARTTRIOPROJECT_API UCollectedItemComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) TObjectPtr<ASeniorPlayer> seniorPlayerRef = nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<AActor> usableItem = nullptr; // TODO Modify

	TArray<TPair<TObjectPtr<UBillboardComponent>, bool>> shoppingKartContentLocation;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_ListItem) TArray<TObjectPtr<ACollectedItem>> listItem;
	UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<ACollectedItem>> listItemCollected;
	UPROPERTY(VisibleAnywhere) int nbItemCollected = 0;
	UPROPERTY(EditAnywhere) int sizeList = 4;
	UPROPERTY(EditAnywhere) bool canFinish = false;
	UPROPERTY(EditAnywhere) float timeCooldown = 2;
	UPROPERTY(EditAnywhere) bool isCooldown = false;

public:
	FORCEINLINE TObjectPtr<ACollectedItem> GetCurrentItem() const { return listItem.IsValidIndex(nbItemCollected) ? listItem[nbItemCollected] : nullptr; }
	FORCEINLINE bool CanFinish() const { return canFinish; }
	FORCEINLINE int GetNumItemCollected() const { return nbItemCollected; }
	FORCEINLINE int GetSizeList() const { return sizeList; }

public:
	UCollectedItemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//UFUNCTION() void UseItem(const FInputActionValue& _valueFloat);
	//UFUNCTION(Server, Unreliable) void SpawnItemServer(const FVector& _position);
	TArray<TObjectPtr<UBillboardComponent>> GetAllBillBoardComponents();
	void UpdateCurrentItem(TObjectPtr<ACollectedItem> _collectItem);
	void AddCollectedItemMeshToShoppingKart(TObjectPtr<ACollectedItem> _collectItem);
	int GetAvailableShoppingKartPosition();
	UFUNCTION() void ResetCooldown();
	UFUNCTION(Server, Reliable) void ServerRPC_PlaceItemInShoppingCart(ACollectedItem* _collectItem, const int _meshIndex);
	UFUNCTION() void OnRep_ListItem();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PlaceItemInShoppingCart(ACollectedItem* _collectItem, const int _meshIndex);
};
