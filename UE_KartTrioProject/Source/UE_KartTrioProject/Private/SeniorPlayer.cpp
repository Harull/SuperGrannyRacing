// Fill out your copyright notice in the Description page of Project Settings.


#include "SeniorPlayer.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "Net/UnrealNetwork.h"
#include <Components/SeniorMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Components/PlaceArrowSignComponent.h"
#include <Online/GIS_Online.h>
#include <GPE/ReplicatedStartManager.h>
#include <Kismet/GameplayStatics.h>
#include "Components/InventoryComponent.h"
#include <GIS/WS_PlayerClassement.h>
#include "UI/Lobby_HUD.h"

// Sets default values
ASeniorPlayer::ASeniorPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	seniorMovementcomponent = CreateDefaultSubobject<USeniorMovementComponent>("MovementComponent");
	collectedItemComponent = CreateDefaultSubobject<UCollectedItemComponent>("CollectedItem");
	placeArrowSignComponent = CreateDefaultSubobject<UPlaceArrowSignComponent>("PlaceArrowSign");
	inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	bumpComponent = CreateDefaultSubobject<UBumpComponent>("Bump");

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
	AddOwnedComponent(inventory);
	AddOwnedComponent(bumpComponent);
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
	onInitializationDone.Broadcast();
	SendNotifyIsReady();
	InitUsername();
}

void ASeniorPlayer::InitUsername()
{
	if (!IsLocallyControlled())return;
	if (HasAuthority())
		steamUsername = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->GetSteamUserName();
	else
		Server_ModifySteamUsername(GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->GetSteamUserName());

}

void ASeniorPlayer::SendNotifyIsReady()
{
	if (GetWorld()->GetFirstPlayerController()->GetCharacter() != this)
	{
		UKismetSystemLibrary::PrintString(this, "ASeniorPlayer::SendNotifyIsReady early return", true, true, FLinearColor::Yellow, 30);
		return;
	}
	UKismetSystemLibrary::PrintString(this, "This character is possessed, and ASeniorPlayer::SendNotifyIsReady is searching for a AReplicatedStartManager", true, true, FLinearColor::Yellow, 30);

	UKismetSystemLibrary::PrintString(this, "Calling the server rpc right away", true, true, FLinearColor::Yellow, 30);
	Server_IncrementCurrentPlayerReady();
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
	//UKismetSystemLibrary::PrintString(this, steamUsername, true, true, FLinearColor::Yellow, 30);

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

	//_inputComponent->BindAction(usePowerup, ETriggerEvent::Started, collectedItemComponent.Get(), &UCollectedItemComponent::UseItem);
	_inputComponent->BindAction(usePowerup, ETriggerEvent::Started, inventory.Get(), &UInventoryComponent::UseItem);

	// Check if we're in the right level
	TObjectPtr<AHUD> _baseHUD = GetWorld()->GetFirstPlayerController()->GetHUD();
	TObjectPtr<ALobby_HUD> _hud = Cast<ALobby_HUD>(_baseHUD);

	_inputComponent->BindAction(openPlayerList, ETriggerEvent::Started, _hud.Get(), &ALobby_HUD::TogglePlayerList);
	//_inputComponent->BindAction(openPlayerList, ETriggerEvent::Completed, _lobby.Get(), &ULobbyWidget::TogglePlayerList);
	_inputComponent->BindAction(useSpecialItem, ETriggerEvent::Started, inventory.Get(), &UInventoryComponent::UseSpecialItem);
	//TODO Implement other bindings


}

void ASeniorPlayer::InitUniqueID()
{
	if (HasAuthority())
		repActorID = this->GetUniqueID();
	actorLocalID = this->GetUniqueID();
}

void ASeniorPlayer::Server_IncrementCurrentPlayerReady_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "THE SERVER RPC IS CALLED", true, true, FLinearColor::Yellow, 30);
	AActor* _actor = UGameplayStatics::GetActorOfClass(this, AReplicatedStartManager::StaticClass());
	if (TObjectPtr<AReplicatedStartManager> _startManager = Cast<AReplicatedStartManager>(_actor))
	{
		_startManager->IncrementCurrentPlayerReady();
	}
}


void ASeniorPlayer::Server_ModifySteamUsername_Implementation(const FString& _steamUsername)
{
	UKismetSystemLibrary::PrintString(this, "rpc CALLED: " + _steamUsername, true, true, FLinearColor::Yellow, 30);
	steamUsername = _steamUsername;
}


void ASeniorPlayer::Client_ApplyMalusEffect_Implementation(UMaterialInterface* _material, float _duration)
{
	UCameraComponent* _camera = FindComponentByClass<UCameraComponent>();
	if (!_camera || !_material) return;

	UMaterialInstanceDynamic* _dynMat = UMaterialInstanceDynamic::Create(_material, this);
	_camera->AddOrUpdateBlendable(_dynMat);

	FTimerHandle _timerHandle;
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, [=]()
		{
			_camera->RemoveBlendable(_dynMat);
		}, _duration, false);
}

void ASeniorPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ASeniorPlayer, repActorID, COND_InitialOnly);
	DOREPLIFETIME(ASeniorPlayer, steamUsername);
}

