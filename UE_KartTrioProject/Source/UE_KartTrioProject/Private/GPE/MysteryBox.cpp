// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/MysteryBox.h"
#include <SeniorPlayer.h>

// Sets default values
AMysteryBox::AMysteryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMysteryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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

