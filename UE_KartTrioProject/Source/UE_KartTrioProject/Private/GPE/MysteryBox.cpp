#include "GPE/MysteryBox.h"
#include <SeniorPlayer.h>

AMysteryBox::AMysteryBox()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMysteryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMysteryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMysteryBox::EnterAction(AActor* OtherActor)
{
	if (TObjectPtr<ASeniorPlayer> _player = Cast<ASeniorPlayer>(OtherActor))
	{
		mesh->SetVisibility(false);

	}
}

