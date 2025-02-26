// Fill out your copyright notice in the Description page of Project Settings.


#include "SeniorPlayer.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values
ASeniorPlayer::ASeniorPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	seniorMovementcomponent = CreateDefaultSubobject<USeniorMovementComponent>("MovementComponent");

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
}

void ASeniorPlayer::BeginPlay()
{
	Super::BeginPlay();
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
	_inputComponent->BindAction(forward, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::MoveForward);
	_inputComponent->BindAction(backward, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::MoveBackward);
	_inputComponent->BindAction(steering, ETriggerEvent::Triggered, seniorMovementcomponent.Get(), &USeniorMovementComponent::SteerWheels);
	//TODO Implement other bindings
}

