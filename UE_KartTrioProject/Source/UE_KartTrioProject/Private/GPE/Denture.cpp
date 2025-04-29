#include "GPE/Denture.h"
#include "SeniorPlayer.h"
#include "Components/SeniorMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>

ADenture::ADenture()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ADenture::BeginPlay()
{
	Super::BeginPlay();
}

void ADenture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Rotate(DeltaTime);
}

void ADenture::Use(ASeniorPlayer* _player)
{
	if (!_player)return;
	UKismetSystemLibrary::PrintString(this, "Spawn", true, true, FLinearColor::Red, 10.0f);
	FVector _position = _player->GetActorLocation() + _player->GetActorForwardVector() * 200.0f;

	FVector _newPos = FVector(_position.X , _position.Y, _position.Z);
	mesh->IgnoreActorWhenMoving(_player, true);
	SetActorLocation(_newPos);
}

void ADenture::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.0f, rotationSpeed * _delta, 0.0f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}

void ADenture::Move(float _delta)
{
	FVector _newLocation = GetActorLocation() + (GetActorForwardVector() * moveSpeed * _delta);
	SetActorLocation(_newLocation);
}

void ADenture::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;
	UKismetSystemLibrary::PrintString(this, "Destroy", true, true, FLinearColor::Red, 10.0f);
	ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor);
	if (_player)
	{
		TObjectPtr<USeniorMovementComponent> _movement = _player->GetSeniorMovementComponent();
		if (!_movement) return;
		_movement->StopMoveAndRotateTime(stunTime);
		Destroy();
	}
	else
	{
		Destroy();
	}
	
}

