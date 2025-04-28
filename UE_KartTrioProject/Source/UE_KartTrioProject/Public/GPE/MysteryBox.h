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
	AMysteryBox();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void EnterAction(AActor* OtherActor) override;

};
