// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DestinationArrowComponent.h"
#include "GPE/DestinationArrow.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UDestinationArrowComponent::UDestinationArrowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UDestinationArrowComponent::BeginPlay()
{
	Super::BeginPlay();
    UKismetSystemLibrary::PrintString(this, "Step 1!", true, true, FLinearColor::Blue, 30);

    if (arrowToSpawn)
    {
        FActorSpawnParameters _spawnParams;
        _spawnParams.Owner = GetOwner();
        _spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector _spawnLocation = GetOwner()->GetActorLocation() + arrowOffset;
        currentArrow = GetWorld()->SpawnActor<ADestinationArrow>(arrowToSpawn, _spawnLocation, FRotator::ZeroRotator, _spawnParams);
        UKismetSystemLibrary::PrintString(this, "Arrow Spawned !", true, true, FLinearColor::Blue, 30);

        if (currentArrow)
        {
            currentArrow->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
        }
    }
	
}

void UDestinationArrowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // currentArrow->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0,0,200));
}

