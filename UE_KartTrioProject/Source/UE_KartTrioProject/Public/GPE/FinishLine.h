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

	UPROPERTY(EditAnywhere,Replicated)int playerFinishCount = 0;

	UPROPERTY()TMap<ASeniorPlayer*, int> playerPlacements;
	UPROPERTY() bool isAvailable = true;

	

	
public:
	FORCEINLINE bool GetIsAvailable() const { return isAvailable; }
	FOnStopRace& OnStopRace() { return onStopRace; }

public:	
	AFinishLine();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	FString GetOrdinalSuffix(int _number);
	void RegisterPlayerFinish(ASeniorPlayer* _player);
	int GetPlayerRank(ASeniorPlayer* _player);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
