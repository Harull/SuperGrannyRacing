#include "GPE/RewardBox.h"
#include "GPE/Item.h"
#include "Components/InventoryComponent.h"

ARewardBox::ARewardBox()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicates(true);

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
	mesh->SetIsReplicated(true);

}

void ARewardBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARewardBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AItem> ARewardBox::GiveRandomItem()
{
	if (!IsValidItemArray())
	{
		return nullptr;
	}

	int _count = availablesItems.Num() - 1;
	int _randomIndex = FMath::RandRange(0, _count);
	return availablesItems[_randomIndex];
}

void ARewardBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	ASeniorPlayer* _player = Cast<ASeniorPlayer>(OtherActor);
	if (_player)
	{
		UInventoryComponent* _inventory = _player->GetComponentByClass<UInventoryComponent>();
		if (!_inventory)return;
		_inventory->AddItem(GiveRandomItem());

		Destroy();
	}
}

