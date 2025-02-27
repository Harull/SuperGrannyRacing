#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ColdZone.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API AColdZone : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> box = nullptr;
	UPROPERTY(EditAnywhere) float ratioSlow = 0.25f;
	
public:	
	AColdZone();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
