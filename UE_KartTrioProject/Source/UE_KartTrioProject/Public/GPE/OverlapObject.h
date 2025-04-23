// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverlapObject.generated.h"

UCLASS(Abstract)
class UE_KARTTRIOPROJECT_API AOverlapObject : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AOverlapObject();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction(AActor* OtherActor) PURE_VIRTUAL(&AOverlapObject::EnterAction, );
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
