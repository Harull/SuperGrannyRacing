// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/ColdZone.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>

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
	float _forward = _movement->GetForwardSpeed() * ratioSlow;
	float _backward = _movement->GetBackwardSpeed() * ratioSlow;
	_movement->SetForwardSpeed(_forward);
	_movement->SetBackwardSpeed(_backward);
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
	_movement->ResetForwardSpeed();
	_movement->ResetBackwardSpeed();
}

