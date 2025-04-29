// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BumpComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "GameFramework/PawnMovementComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values for this component's properties
UBumpComponent::UBumpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UBumpComponent::BeginPlay()
{
	Super::BeginPlay();
	DesactivatedBoxes();
	
}

void UBumpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	ApplyBumpToAll(BoxCastAll());
}

void UBumpComponent::DesactivatedBoxes()
{
	for (TObjectPtr<UBoxComponent> _component : bumpBoxes)
		if (_component) _component->SetActive(false);
}

TArray<FHitResult> UBumpComponent::BoxCastAll()
{
	TArray<FHitResult> _toReturn;

	for (TObjectPtr<UBoxComponent> _box : bumpBoxes)
	{
		if (!_box)continue;
		TArray<FHitResult> _localResult;
		UKismetSystemLibrary::BoxTraceMultiForObjects(this, _box->GetComponentLocation(), _box->GetComponentLocation(), _box->GetScaledBoxExtent(), _box->GetComponentRotation(),
			bumpableLayers, false, {}, EDrawDebugTrace::ForOneFrame, _localResult, true);

		if (_localResult.Num() > 0)
		{
			UKismetSystemLibrary::PrintString(this, "The boxtrace wasnt empty", true, true, FLinearColor::Gray);
			_toReturn.Append(_localResult);
		}
	}

	return _toReturn;
}

void UBumpComponent::ApplyBumpToAll(const TArray<FHitResult>& _results)
{
	for (auto& _result : _results)
	{
		UKismetSystemLibrary::PrintString(this, "Trying to apply bump", true, true, FLinearColor::Gray);

		//_result.GetActor()->GetComponentByClass<UPawnMovementComponent>()
		if (TObjectPtr<UCharacterMovementComponent> _characterMovementCmpnt = _result.GetActor()->GetComponentByClass<UCharacterMovementComponent>())
		{
			UKismetSystemLibrary::PrintString(this, "DID apply bump", true, true, FLinearColor::Gray);
			_characterMovementCmpnt->AddForce(FVector(9999,9999,9999)/*-_result.ImpactNormal * bumpStrength*/); //TODO (lerp by owners velocity if have the corresponding component)
		}
		//else if (TObjectPtr<UPawnMovementComponent> _pawnMovementCmpnt = _result.GetActor()->GetComponentByClass<UPawnMovementComponent>())
			//_pawnMovementCmpnt->AddRadialImpulse(_result .-_result.ImpactNormal * bumpStrength);
		else
			UKismetSystemLibrary::PrintString(this, "Error, trying to apply a bump to an actor not in the possession of a character movement component. => UBumpComponent::ApplyBumpToAll", true, true, FLinearColor::Red);
		//if(_result.GetActor())
	}
}

void UBumpComponent::AddBoxToBumpBoxes(UBoxComponent* _box)
{
	bumpBoxes.Add(_box);
}

