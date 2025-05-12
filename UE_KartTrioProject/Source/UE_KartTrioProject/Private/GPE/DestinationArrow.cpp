// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/DestinationArrow.h"
#include <GPE/FinishLine.h>
#include <Kismet/GameplayStatics.h>
#include "FinishLineSubsystem.h"
#include <SeniorPlayer.h>

// Sets default values
ADestinationArrow::ADestinationArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	arrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("ArrowMesh");

	arrowMesh->SetupAttachment(RootComponent);

}

void ADestinationArrow::SetTarget(const FVector& _newTarget)
{
	targetPoint = _newTarget;
}

void ADestinationArrow::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(updateTargetTimerHandle, this, &ADestinationArrow::UpdateTargetPoint, 2.0f, true);
}


void ADestinationArrow::UpdateTargetPoint()
{
	if (shoppingListCompleted)
	{
		if (UFinishLineSubsystem* _sub = GetWorld()->GetSubsystem<UFinishLineSubsystem>())
		{
			if (AFinishLine* _nearestFinish = _sub->GetClosestAvailableFinishLine(GetActorLocation()))
			{
				targetPoint = _nearestFinish->GetActorLocation();
			}
		}
	}
}


// Called every frame
void ADestinationArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!targetPoint.IsNearlyZero())
	{
		arrowMesh->SetVisibility(true);
		FVector _arrowLocation = GetActorLocation();
		FVector _direction = targetPoint - _arrowLocation;

		_direction.Z = 0.f;

		if (!_direction.IsNearlyZero())
			SetActorRotation(_direction.Rotation());
	}
	else
	{
		arrowMesh->SetVisibility(false);
	}

}




