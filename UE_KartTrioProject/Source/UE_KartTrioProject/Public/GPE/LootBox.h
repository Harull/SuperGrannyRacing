#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootBox.generated.h"

class AItem;
class ALootBoxSpawnPoint;

UCLASS()
class UE_KARTTRIOPROJECT_API ALootBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere) float rotationSpeed = 250.0f;
	UPROPERTY(EditAnywhere) float levitateSpeed = 250.0f;
	UPROPERTY(EditAnywhere) float levitateAmplitude = 250.0f;

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AItem>> availablesItems;
	UPROPERTY(EditAnywhere)TWeakObjectPtr<ALootBoxSpawnPoint> owningSpawnPoint;


	float runningTime = 0.0f;

private:
	FORCEINLINE bool IsValidItemArray()
	{
		return availablesItems.Num() > 0;
	}
	
public:	
	ALootBox();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void Levitate(float _delta);
	void Rotate(float _delta);
	TSubclassOf<AItem> GiveRandomItem();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	void SetOwningSpawnPoint(ALootBoxSpawnPoint* _spawnPoint);

};
