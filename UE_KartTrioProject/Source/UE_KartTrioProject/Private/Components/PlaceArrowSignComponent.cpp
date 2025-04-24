#include "Components/PlaceArrowSignComponent.h"
#include "UI/ArrowSign.h"

UPlaceArrowSignComponent::UPlaceArrowSignComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlaceArrowSignComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlaceArrowSignComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlaceArrowSignComponent::PlaceArrowNewPosition(const FVector& _targetPosition)
{
	DestroyCurrentArrow();
	if (!arrowToSpawn) return;

	// TODO Add offset for up position
	FVector _position = _targetPosition + FVector(0, 0, zOffset);
	currentArrow = GetWorld()->SpawnActor<AArrowSign>(arrowToSpawn, _position, FRotator());
}

void UPlaceArrowSignComponent::NoMoreItem()
{
	DestroyCurrentArrow();
}

void UPlaceArrowSignComponent::DestroyCurrentArrow()
{
	if (currentArrow) currentArrow->Destroy();
	currentArrow = nullptr;
}