// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CollectedItem.generated.h"

/**
 * 
 */
UCLASS()
class UE_KARTTRIOPROJECT_API ACollectedItem : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> box = nullptr;
	UPROPERTY(EditAnywhere) FString itemName;
	UPROPERTY(EditAnywhere) bool isInTheList = false;
	UPROPERTY(VisibleAnywhere) FVector boxPosition = FVector();

public:
	FORCEINLINE const FVector& GetItemPosition() { return boxPosition; }
	FORCEINLINE FString GetItemName() const { return itemName; }
	FORCEINLINE bool GetIsInList() const { return isInTheList; }
	FORCEINLINE void SetIsInTheList(bool _value) { isInTheList = _value; }

public:
	ACollectedItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void Init();
};
