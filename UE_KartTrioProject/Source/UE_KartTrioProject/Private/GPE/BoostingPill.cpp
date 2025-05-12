#include "GPE/BoostingPill.h"
#include "Components/SeniorMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "GIS/WS_PlayerClassement.h"


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

//void ABoostingPill::Use(ASeniorPlayer* _target)
//{
//	if (!_target)return;
//	USeniorMovementComponent* _movement = _target->GetComponentByClass<USeniorMovementComponent>();
//	if (!_movement)return;
//	float _forward = _movement->GetForwardMaxSpeed() * boostRatio;
//	float _backward = _movement->GetBackwardMaxSpeed() * boostRatio;
//	_movement->SetForwardMaxSpeed(_forward);
//	_movement->SetBackwardMaxSpeed(_backward);
//
//	UCameraComponent* _camera = _target->FindComponentByClass<UCameraComponent>();
//	if (_camera)
//	{
//		float _originalFOV = _camera->FieldOfView;
//		float _boostFOV = _originalFOV + 30.0f; 
//		_camera->SetFieldOfView(_boostFOV);
//
//		UKismetSystemLibrary::PrintString(this, "Rest");
//		FTimerHandle _fovResetTimer;
//		GetWorld()->GetTimerManager().SetTimer(_fovResetTimer, [_camera, _originalFOV]()
//			{
//				_camera->SetFieldOfView(_originalFOV);
//			}, boostTime, false);
//	}
//
//
//	FTimerHandle _timer;
//	GetWorld()->GetTimerManager().SetTimer(_timer, [_movement]()
//		{
//			_movement->ResetForwardMaxSpeed();
//			_movement->ResetBackwardMaxSpeed();
//
//		}, boostTime, false);
//
//	
//}



void ABoostingPill::Use(ASeniorPlayer* _target)
{
	if (!_target) return;
	
	USeniorMovementComponent* _movement = _target->GetSeniorMovementComponent();
	if (!_movement)return;
	UKismetSystemLibrary::PrintString(this, "Activate");
	//_movement->ActivateSpeedBoost();
	_target->ActivateSpeedBoost();

}



