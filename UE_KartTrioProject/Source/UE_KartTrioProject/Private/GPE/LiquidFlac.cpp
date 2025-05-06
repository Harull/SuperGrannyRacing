#include "GPE/LiquidFlac.h"
#include "SeniorPlayer.h"
#include "Components/SeniorMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>

ALiquidFlac::ALiquidFlac()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
	name = "Liquid Flac";
}

void ALiquidFlac::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALiquidFlac::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALiquidFlac::Use(ASeniorPlayer* _player)
{
	UKismetSystemLibrary::PrintString(this, " Before" );
	if (!_player)return;
	FVector _position = _player->GetActorLocation() + _player->GetActorForwardVector() * -200.0f;
	UKismetSystemLibrary::PrintString(this, FString::FromInt(_position.X) + " " + FString::FromInt(_position.Y));
	FVector _newPos = FVector(_position.X, _position.Y, 0.0f);
	SetActorLocation(_newPos);
}

void ALiquidFlac::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;
	ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor);
	if (!_player)return;

	TObjectPtr<USeniorMovementComponent> _movement = _player->GetSeniorMovementComponent();
	if (!_movement) return;

	UKismetSystemLibrary::PrintString(this, "Stun");
	_movement->StopMoveAndRotateTime(stunTime);
	Destroy();



}

