// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE/OverlapObject.h"
#include "MysteryBox.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API AMysteryBox : public AOverlapObject
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AActor>> allTypeItems;

public:	
	// Sets default values for this actor's properties
	AMysteryBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction(AActor* OtherActor) override;

};
