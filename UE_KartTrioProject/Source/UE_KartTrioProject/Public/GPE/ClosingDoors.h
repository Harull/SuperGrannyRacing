
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClosingDoors.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API AClosingDoors : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> doorLeft = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> doorRight = nullptr;
	
public:	
	AClosingDoors();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(Server, Unreliable)  void ClosingDoor();
	UFUNCTION(Server, Unreliable)  void OpenDoor();

private:
	void LerpMovingDoor(const float _factor);

};