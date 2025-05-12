// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinationArrow.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API ADestinationArrow : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Arrow")	TObjectPtr<UStaticMeshComponent> arrowMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Arrow") FVector targetPoint;
	UPROPERTY(EditAnywhere, Category = "Arrow") FRotator straightAheadRotation;
	UPROPERTY(EditAnywhere, Category = "Arrow") bool shoppingListCompleted;
	
public:	
	FORCEINLINE void ToggleVisibility() { arrowMesh->SetVisibility(!arrowMesh->IsVisible()); }
	FORCEINLINE FRotator GetStraightAheadRotation() { return straightAheadRotation; }
	FORCEINLINE void SetShoppingListCompleted(const bool _bool) { shoppingListCompleted = _bool; }
	ADestinationArrow();
	void SetTarget(const FVector& _newDestination);
	bool IsStraightAheadItsDestination();
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
