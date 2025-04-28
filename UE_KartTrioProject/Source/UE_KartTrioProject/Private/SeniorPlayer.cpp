// Fill out your copyright notice in the Description page of Project Settings.


#include "SeniorPlayer.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "Net/UnrealNetwork.h"
#include <Components/SeniorMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Components/PlaceArrowSignComponent.h"
#include <Online/GIS_Online.h>

// Sets default values
ASeniorPlayer::ASeniorPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	seniorMovementcomponent = CreateDefaultSubobject<USeniorMovementComponent>("MovementComponent");
	collectedItemComponent = CreateDefaultSubobject<UCollectedItemComponent>("CollectedItem");
	placeArrowSignComponent = CreateDefaultSubobject<UPlaceArrowSignComponent>("PlaceArrowSign");

	//CAMERA
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera->SetupAttachment(springArm);
	springArm->SetupAttachment(RootComponent);

	//COMPOSED MESH OF CART
	cartCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CartCapsule");
	shoppingCart = CreateDefaultSubobject<UStaticMeshComponent>("ShoppingCart");
	backWheels = CreateDefaultSubobject<UStaticMeshComponent>("BackWheels");
	frontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>("FrontRightWheel");
	frontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>("FrontLeftWheel");

	cartCapsuleComponent->SetupAttachment(RootComponent);
	shoppingCart->SetupAttachment(cartCapsuleComponent);
	backWheels->SetupAttachment(shoppingCart);
	frontRightWheel->SetupAttachment(shoppingCart);
	frontLeftWheel->SetupAttachment(shoppingCart);

	AddOwnedComponent(seniorMovementcomponent);
	AddOwnedComponent(collectedItemComponent);
	AddOwnedComponent(placeArrowSignComponent);
}

void ASeniorPlayer::SetMovementActive(bool _isActive)
{
	seniorMovementcomponent->SetCanMove(_isActive);
	seniorMovementcomponent->SetCanRotate(_isActive);
	seniorMovementcomponent->SetCanSteerWheels(_isActive);
}

void ASeniorPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitUniqueID();
	SetReplicateMovement(false); //somehow the replicate movement fcks up client side movements inputs, so need to replicate it myself
	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, this, &ASeniorPlayer::PrintDebug, 5.F, true);
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(repActorID), true, true, FLinearColor::Gray, 10.0f); // TODO Remove
	
	FString _steamName = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->GetSteamUserName();
	UKismetSystemLibrary::PrintString(this, _steamName); // TODO Remove
}

void ASeniorPlayer::PrintDebug()
{
	//UKismetSystemLibrary::PrintString(this, "Current Player count from GIS online: " +
	//	FString::FromInt(GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->GetPlayerCount()));
}

// Called every frame
void ASeniorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeniorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitSubsystem();
	InitInputs(Cast<UEnhancedInputComponent>(PlayerInputComponent));

}

void ASeniorPlayer::InitSubsystem()
{
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> _subsys = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_subsys) {
		UE_LOG(LogTemp, Warning, TEXT("ERROR WHILE INITIALIZING ASeniorPlayer's input subsystem, _subsys null -> "));
		return;
	}
	_subsys->AddMappingContext(mapping, 0);
}

void ASeniorPlayer::InitInputs(TObjectPtr<UEnhancedInputComponent> _inputComponent)
{
	if (!_inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR WHILE INITIALIZING ASeniorPlayer's inputs,  _inputComponent null -> ASeniorPlayer::InitInputs"));
		return;
	}
	_inputComponent->BindAction(forward, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::AddVelocity);
	_inputComponent->BindAction(backward, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::SubstractVelocity);
	_inputComponent->BindAction(steering, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::SteerWheels);

	_inputComponent->BindAction(forward, ETriggerEvent::Started, seniorMovementcomponent.Get(), &USeniorMovementComponent::SetIsMovingForward);
	_inputComponent->BindAction(forward, ETriggerEvent::Completed, seniorMovementcomponent.Get(), &USeniorMovementComponent::SetIsMovingForward);

	_inputComponent->BindAction(backward, ETriggerEvent::Started, seniorMovementcomponent.Get(), &USeniorMovementComponent::SetIsMovingBackward);
	_inputComponent->BindAction(backward, ETriggerEvent::Completed, seniorMovementcomponent.Get(), &USeniorMovementComponent::SetIsMovingBackward);

	_inputComponent->BindAction(usePowerup, ETriggerEvent::Started, collectedItemComponent.Get(), &UCollectedItemComponent::UseItem);
	//TODO Implement other bindings
	}

void ASeniorPlayer::InitUniqueID()
{
	if (HasAuthority())
		repActorID = this->GetUniqueID();
	actorLocalID = this->GetUniqueID();
}

void ASeniorPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ASeniorPlayer, repActorID, COND_InitialOnly);
}

