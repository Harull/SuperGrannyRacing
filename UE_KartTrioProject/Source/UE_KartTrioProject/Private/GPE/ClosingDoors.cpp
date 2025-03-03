
#include "GPE/ClosingDoors.h"

AClosingDoors::AClosingDoors()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	doorLeft = CreateDefaultSubobject<UStaticMeshComponent>("DoorLeft");
	doorRight = CreateDefaultSubobject<UStaticMeshComponent>("DoorRight");

	doorLeft->SetupAttachment(RootComponent);
	doorRight->SetupAttachment(RootComponent);

}

void AClosingDoors::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClosingDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClosingDoors::ClosingDoor_Implementation()
{

}

void AClosingDoors::OpenDoor_Implementation()
{

}

void AClosingDoors::LerpMovingDoor(const float _factor)
{

}