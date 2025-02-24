// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/Puddle.h"
#include <Kismet/KismetSystemLibrary.h>

APuddle::APuddle()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APuddle::BeginPlay()
{
	Super::BeginPlay();
}

void APuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuddle::EnterAction()
{
}
