// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CollectedItemComponent.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UCollectedItemComponent::UCollectedItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollectedItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollectedItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollectedItemComponent::UseItem(const FInputActionValue& _valueFloat)
{
	if (!usableItem) return;
	UKismetSystemLibrary::PrintString(this, "UseItem");
	FVector _position = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * -100.0f;


	if(!GetOwner()->HasAuthority())
		SpawnItemServer(_position);
	else
		GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));
}

void UCollectedItemComponent::UpdateCurrentItem(TObjectPtr<ACollectedItem> _collectItem)
{
	if (_collectItem == GetCurrentItem()) nbItemCollected++;
}

void UCollectedItemComponent::SpawnItemServer_Implementation(const FVector& _position)
{
	GetWorld()->SpawnActor<AActor>(usableItem, _position, FRotator(0));
}