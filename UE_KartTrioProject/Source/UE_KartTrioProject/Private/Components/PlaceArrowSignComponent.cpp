#include "Components/PlaceArrowSignComponent.h"
#include "UI/ArrowSign.h"
#include <Kismet/KismetSystemLibrary.h>

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
	UKismetSystemLibrary::PrintString(this, "TRY PlaceArrow");
	DestroyCurrentArrow();
	if (!arrowToSpawn) return;

	// TODO Add offset for up position
	FVector _position = _targetPosition + offset;
	currentArrow = GetWorld()->SpawnActor<AArrowSign>(arrowToSpawn, _position, FRotator());
	UKismetSystemLibrary::PrintString(this, "PlaceArrow");
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