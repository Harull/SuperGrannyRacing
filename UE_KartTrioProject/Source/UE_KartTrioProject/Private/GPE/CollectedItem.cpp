
// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/CollectedItem.h"
#include "GIS/GIS_CollectedItem.h"
#include <SeniorPlayer.h>
#include <Kismet/KismetSystemLibrary.h>

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
	if (!isInTheList) return;
	//TODO ADD item to player
	ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor);

	if (!_player) return;

	UCollectedItemComponent* _comp =  _player->GetCollectedItemComponent();

	if (!_comp) return;

	//UKismetSystemLibrary::PrintString(this, _comp->GetOwner()->GetName());
	_comp->UpdateCurrentItem(this);
}

void ACollectedItem::Init()
{
	if (!isInTheList) return;
	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
	_sub->AddCollectedItem(this);
}
