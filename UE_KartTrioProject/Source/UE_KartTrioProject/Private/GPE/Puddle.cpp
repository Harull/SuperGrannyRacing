// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/Puddle.h"
#include <Kismet/KismetSystemLibrary.h>
#include "SeniorPlayer.h"

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
	if (ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor))
	{
		TObjectPtr<USeniorMovementComponent> _movement =  _player->GetComponentByClass<USeniorMovementComponent>();
		if (!_movement) return;

		/*FTimerHandle _timer;
		FTimerDelegate _delegate;
		_delegate.BindLambda([&]()
			{
				_movement->SetCanMove(true);
				_movement->SetCanRotate(true);
			});
		GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, timeStun, false);*/

		/*_movement->SetCanMove(false);
		_movement->SetCanRotate(false);

		UKismetSystemLibrary::Delay(this, timeStun * 1000, FLatentActionInfo());

		UKismetSystemLibrary::PrintString(this, "End Stun");

		_movement->SetCanMove(true);
		_movement->SetCanRotate(true);*/
	}
}


