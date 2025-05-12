// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/DestinationArrow.h"
#include <GPE/FinishLine.h>
#include <Kismet/GameplayStatics.h>
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

bool ADestinationArrow::IsStraightAheadItsDestination()
{
	GetActorRotation();

	FVector _arrowLocation = GetActorLocation();
	FVector _direction = targetPoint - _arrowLocation;

	const float _dot = FVector::DotProduct(_arrowLocation.GetSafeNormal(), _direction.GetSafeNormal());
	return _dot <= 1;
}


// Called when the game starts or when spawned
void ADestinationArrow::BeginPlay()
{
	Super::BeginPlay();


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
	else if (shoppingListCompleted)
	{
		if (AFinishLine* _fnl = Cast<AFinishLine>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinishLine::StaticClass())))
			targetPoint = _fnl->GetActorLocation();
	}
	else
	{
		arrowMesh->SetVisibility(false);
	}
	//if (IsStraightAheadItsDestination())
	//{
	//    SetActorRotation(straightAheadRotation);
	//}
}




