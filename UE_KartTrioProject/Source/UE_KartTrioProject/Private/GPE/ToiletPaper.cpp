#include "GPE/ToiletPaper.h"
#include "SeniorPlayer.h"

AToiletPaper::AToiletPaper()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);

}

void AToiletPaper::BeginPlay()
{
	Super::BeginPlay();
	
}

void AToiletPaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToiletPaper::Use(ASeniorPlayer* _player)
{
	if (!_player)return;
	FVector _position = _player->GetActorLocation() + _player->GetActorForwardVector() * -100.0f;

	FVector _newPos = FVector(_position.X, _position.Y, 0.0f);
	SetActorLocation(_newPos);
}

