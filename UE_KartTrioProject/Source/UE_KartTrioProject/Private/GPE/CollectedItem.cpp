
// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/CollectedItem.h"
#include "GIS/GIS_CollectedItem.h"

ACollectedItem::ACollectedItem()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	box = CreateDefaultSubobject<UBoxComponent>("Box");

	mesh->SetupAttachment(RootComponent);
	box->SetupAttachment(RootComponent);
}

void ACollectedItem::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ACollectedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectedItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//TODO ADD item to player

}

void ACollectedItem::Init()
{
	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
	_sub->AddCollectedItem(this);
}
