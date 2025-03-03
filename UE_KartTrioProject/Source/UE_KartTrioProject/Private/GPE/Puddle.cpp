// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/Puddle.h"
#include <Kismet/KismetSystemLibrary.h>
#include "SeniorPlayer.h"
#include "Components/SeniorMovementComponent.h"

APuddle::APuddle()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void APuddle::BeginPlay()
{
	Super::BeginPlay();
}

void APuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuddle::EnterAction(AActor* OtherActor)
{
	if (TObjectPtr<ASeniorPlayer> _player = Cast<ASeniorPlayer>(OtherActor))
	{
		//UKismetSystemLibrary::PrintString(this, "Enter action and has a good movemnt component, reseting it");

		//TObjectPtr<USeniorMovementComponent> _movement =  _player->GetComponentByClass<USeniorMovementComponent>();
		TObjectPtr<USeniorMovementComponent> _movement = _player->GetSeniorMovementComponent();
		if (!_movement) return;

		UKismetSystemLibrary::PrintString(this, "Stun");
		_movement->StopMoveAndRotateTime(timeStun);
		SetLifeSpan(timeStun);

	}
}

void APuddle::DeactivateInputs()
{

}

void APuddle::ActivateInputs()
{

}


