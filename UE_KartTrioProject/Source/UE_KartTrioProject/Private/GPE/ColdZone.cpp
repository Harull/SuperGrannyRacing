// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/ColdZone.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/SeniorMovementComponent.h"

AColdZone::AColdZone()
{

	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	box = CreateDefaultSubobject<UBoxComponent>("Box");
	
	mesh->SetupAttachment(RootComponent);
	box->SetupAttachment(RootComponent);
	//AddOwnedComponent(box);
}

void AColdZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AColdZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColdZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	TObjectPtr<ASeniorPlayer> _player = Cast<ASeniorPlayer>(OtherActor);
	if (!_player) return;
	TObjectPtr<USeniorMovementComponent> _movement = _player->GetComponentByClass<USeniorMovementComponent>();
	if (!_movement) return;
	float _forward = _movement->GetForwardMaxSpeed() * ratioSlow;
	float _backward = _movement->GetBackwardMaxSpeed() * ratioSlow;
	_movement->SetForwardMaxSpeed(_forward);
	_movement->SetBackwardMaxSpeed(_backward);
	UKismetSystemLibrary::PrintString(this, "Slow Start");
}

void AColdZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	UKismetSystemLibrary::PrintString(this, "Slow End");
	TObjectPtr<ASeniorPlayer> _player = Cast<ASeniorPlayer>(OtherActor);
	if (!_player) return;
	TObjectPtr<USeniorMovementComponent> _movement = _player->GetComponentByClass<USeniorMovementComponent>();
	if (!_movement) return;
	/*_movement->ResetForwardMaxSpeed();
	_movement->ResetBackwardMaxSpeed();*/
	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, [_movement]()
		{
			_movement->ResetForwardMaxSpeed();
			_movement->ResetBackwardMaxSpeed();

		}, slowTime, false);
	_player->SetTemporaryStatus(EPlayerStatus::FROZEN, slowTime);
}

