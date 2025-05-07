#include "GPE/FlashLight.h"
#include "GIS/WS_PlayerClassement.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = nullptr;
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlashLight::Use(ASeniorPlayer* _target)
{
	if (!_target) return;
	UWS_PlayerClassement* _classementSystem = GetWorld()->GetSubsystem<UWS_PlayerClassement>();
	if (_classementSystem)
	{
		const int _count = _classementSystem->GetAllPlayerCollectedItemComponent().Num();

		for (int i = 0; i < _count; i++)
		{
			ASeniorPlayer* _player = Cast<ASeniorPlayer>(_classementSystem->GetAllPlayerCollectedItemComponent()[i]->GetOwner());
			if (!_player || _player == _target)continue;

			_player->Client_ApplyMalusEffect(malusMaterial, time);

		}
	}
}

