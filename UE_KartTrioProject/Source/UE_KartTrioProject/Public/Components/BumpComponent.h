// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/BoxComponent.h>
#include "BumpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API UBumpComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<UBoxComponent>> bumpBoxes;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> bumpableLayers;
	UPROPERTY(EditAnywhere) float bumpStrength = 10.f;

public:	
	UBumpComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void DesactivatedBoxes();
	TArray<FHitResult> BoxCastAll();
	void ApplyBumpToAll(const TArray<FHitResult>& _results);

public:
	UFUNCTION(BlueprintCallable) void AddBoxToBumpBoxes(UBoxComponent* _box);
};
