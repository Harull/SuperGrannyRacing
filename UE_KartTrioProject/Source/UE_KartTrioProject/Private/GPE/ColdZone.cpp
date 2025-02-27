// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/ColdZone.h"


AColdZone::AColdZone()
{

	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	mesh->SetupAttachment(RootComponent);
	
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
}

void AColdZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

