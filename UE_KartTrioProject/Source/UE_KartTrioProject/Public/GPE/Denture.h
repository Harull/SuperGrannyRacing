#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "Denture.generated.h"

class ASeniorPlayer;

UCLASS()
class UE_KARTTRIOPROJECT_API ADenture : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float stunTime = 2.0f;
	UPROPERTY(EditAnywhere)	float rotationSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)	float moveSpeed = 1000.0f;
	
public:	
	ADenture();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(ASeniorPlayer* _player)override;
private:
	void Rotate(float _delta);
	void Move(float _delta);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
