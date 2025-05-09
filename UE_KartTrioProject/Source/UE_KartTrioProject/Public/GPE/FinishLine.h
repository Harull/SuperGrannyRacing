// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "FinishLine.generated.h"

class ASeniorPlayer;
class UCollectedItemComponent;

UCLASS()
class UE_KARTTRIOPROJECT_API AFinishLine : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopRace);
	
	FOnStopRace onStopRace;
	
	//UPROPERTY(EditAnywhere) TObjectPtr<UBillboardComponent> billboard = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> box = nullptr;

	UPROPERTY(Replicated) TArray<ASeniorPlayer*> arrivedPlayers;
	
public:
	FOnStopRace& OnStopRace() { return onStopRace; }
	FORCEINLINE TArray<ASeniorPlayer*> GetArrivedPlayers(){return arrivedPlayers;}

public:	
	AFinishLine();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	FString GetOrdinalSuffix(int _number);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
