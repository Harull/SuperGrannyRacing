// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/BoxComponent.h>
#include "BumpComponent.generated.h"

class USeniorMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API UBumpComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<UBoxComponent>> bumpBoxes;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> bumpableLayers;
	UPROPERTY(EditAnywhere, meta=(UImin="50000", UIMax="900000", ClampMin="50000", ClampMax="900000")) float bumpStrength = 500000.f;
	UPROPERTY() TObjectPtr<USeniorMovementComponent> personalMovementComponent = nullptr;
public:	
	UBumpComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Init();
	void InitFields();
	void DesactivatedBoxes();

private:
	TArray<FHitResult> BoxCastAll();
	void ApplyBumpToAll(const TArray<FHitResult>& _results);

public:
	UFUNCTION(BlueprintCallable) void AddBoxToBumpBoxes(UBoxComponent* _box);
};
