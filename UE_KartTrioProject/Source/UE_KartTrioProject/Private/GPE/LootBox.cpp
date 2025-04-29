#include "GPE/LootBox.h"
#include "GPE/Item.h"
#include "Components/InventoryComponent.h"

ALootBox::ALootBox()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicates(true);

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
	mesh->SetIsReplicated(true);

}

void ALootBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALootBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Levitate(DeltaTime);
	Rotate(DeltaTime);

}

void ALootBox::Levitate(float _delta)
{
	FVector _loc = GetActorLocation();
	_loc.Z += FMath::Sin(runningTime * levitateSpeed) * levitateAmplitude * _delta;

	SetActorLocation(_loc);
	runningTime += _delta;
}

void ALootBox::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}

TSubclassOf<AItem> ALootBox::GiveRandomItem()
{
	if (!IsValidItemArray())
	{
		return nullptr;
	}

	int _count = availablesItems.Num() - 1;
	int _randomIndex = FMath::RandRange(0, _count);
	return availablesItems[_randomIndex];
}

void ALootBox::NotifyActorBeginOverlap(AActor* OtherActor)
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

