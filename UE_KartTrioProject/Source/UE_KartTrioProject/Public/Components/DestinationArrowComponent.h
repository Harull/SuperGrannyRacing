// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestinationArrowComponent.generated.h"

class ADestinationArrow;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API UDestinationArrowComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Arrow") TSubclassOf<ADestinationArrow> arrowToSpawn = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Arrow") TObjectPtr<ADestinationArrow> currentArrow = nullptr;
	UPROPERTY(EditAnywhere, Category = "Arrow")	FVector arrowOffset = FVector(0.f, 0.f, 200.f);

public:	
	FORCEINLINE TObjectPtr<ADestinationArrow> GetCurrentArrow() { return currentArrow; }
	UDestinationArrowComponent();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
