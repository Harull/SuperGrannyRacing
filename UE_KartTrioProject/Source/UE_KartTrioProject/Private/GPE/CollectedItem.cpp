
// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/CollectedItem.h"
#include "GIS/GIS_CollectedItem.h"
#include <SeniorPlayer.h>
#include <Kismet/KismetSystemLibrary.h>
#include "GPE/Item.h"

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
	//UKismetSystemLibrary::PrintString(this, "Hi1", true, true, FLinearColor::Blue, 10.0f);
	if (!isInTheList) return;
	//TODO ADD item to player
	ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor);
	//UKismetSystemLibrary::PrintString(this, "Hi2", true, true, FLinearColor::Blue, 10.0f);

	if (!_player) return;

	UCollectedItemComponent* _comp =  _player->GetCollectedItemComponent();
	//UKismetSystemLibrary::PrintString(this, "Hi3", true, true, FLinearColor::Blue, 10.0f);

	if (!_comp) return;

	//UKismetSystemLibrary::PrintString(this, _comp->GetOwner()->GetName());
	//UKismetSystemLibrary::PrintString(this, "Hi4", true, true, FLinearColor::Blue, 10.0f);

	_comp->UpdateCurrentItem(this/*, GiveItem()*/);
}

void ACollectedItem::Init()
{
	//if (!isInTheList) return;

	boxPosition = box->GetComponentLocation();

	UGIS_CollectedItem* _sub = GetWorld()->GetSubsystem<UGIS_CollectedItem>();
	_sub->AddCollectedItem(this);
}

//TSubclassOf<AItem> ACollectedItem::GiveItem()
//{
//	if (rewardItems.IsEmpty())return nullptr;
//	int _count = rewardItems.Num() - 1;
//	int _rand = FMath::RandRange(0, _count);
//	TSubclassOf<AItem> _rewardItem = rewardItems[_rand];
//	return _rewardItem;
//}
