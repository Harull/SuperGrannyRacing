#include "GPE/BoostingPill.h"
#include "Components/SeniorMovementComponent.h"

ABoostingPill::ABoostingPill()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = nullptr;
}

void ABoostingPill::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoostingPill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoostingPill::Use(ASeniorPlayer* _target)
{
	if (!_target)return;
	USeniorMovementComponent* _movement = _target->GetComponentByClass<USeniorMovementComponent>();
	if (!_movement)return;
	float _forward = _movement->GetForwardMaxSpeed() * boostRatio;
	float _backward = _movement->GetBackwardMaxSpeed() * boostRatio;
	_movement->SetForwardMaxSpeed(_forward);
	_movement->SetBackwardMaxSpeed(_backward);

	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, [_movement]()
		{
			_movement->ResetForwardMaxSpeed();
			_movement->ResetBackwardMaxSpeed();

		}, boostTime, false);
	
}

