#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowSign.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API AArrowSign : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(VisibleAnywhere) FVector currentPosition = FVector();
	UPROPERTY(VisibleAnywhere) FRotator currentRotation = FRotator();
	
	UPROPERTY(EditAnywhere) float upDownSpeed = 50.0f;
	UPROPERTY(EditAnywhere) float rotateSpeed = 50.0f;
	UPROPERTY(VisibleAnywhere) float timePassed = 0.0f;

public:	
	AArrowSign();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void SetPosition(const FVector& _position);

private:
	void ArrowMovement(float _deltaTime);
	void UpAndDown(float _deltaTime);
	void Rotate(float _deltaTime);
};