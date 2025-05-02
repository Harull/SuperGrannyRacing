#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RewardBox.generated.h"

class AItem;

UCLASS()
class UE_KARTTRIOPROJECT_API ARewardBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)	TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AItem>> availablesItems;

private:
	FORCEINLINE bool IsValidItemArray()
	{
		return availablesItems.Num() > 0;
	}
	
public:	
	ARewardBox();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	TSubclassOf<AItem> GiveRandomItem();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
