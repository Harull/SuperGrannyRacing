// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputMappingContext.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/CapsuleComponent.h"
#include <Camera/CameraComponent.h>
#include "Components/CollectedItemComponent.h"
#include "Net/UnrealNetwork.h"
#include <Components/BumpComponent.h>
#include "SeniorPlayer.generated.h"

class USeniorMovementComponent;
class UPlaceArrowSignComponent;
class UDestinationArrowComponent;
class UInventoryComponent;
class UMainWidget;

UENUM()
enum class EPlayerStatus 
{
	NONE,
	STUN,
	FROZEN,
	SLIPPING
};

UCLASS()
class UE_KARTTRIOPROJECT_API ASeniorPlayer : public ACharacter
{
	GENERATED_BODY()

	//This variable will be used in order to compare ASeniorPlayer when networking (ps in the end i didnt use the replicated one bruh)
	UPROPERTY(VisibleAnywhere, Category = "DEBUG ACTOR ID", Replicated) uint32 repActorID;
	UPROPERTY(VisibleAnywhere, Category = "DEBUG ACTOR ID") uint32 actorLocalID;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<USeniorMovementComponent> seniorMovementcomponent;
private:
	UPROPERTY(EditAnywhere) TObjectPtr<UCollectedItemComponent> collectedItemComponent;
	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera;
	UPROPERTY(EditAnywhere) TObjectPtr<UPlaceArrowSignComponent> placeArrowSignComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess)) TObjectPtr<UInventoryComponent> inventory;
	UPROPERTY(EditAnywhere) TObjectPtr<UDestinationArrowComponent> destinationArrowComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess=True)) TObjectPtr<UBumpComponent> bumpComponent;

	UPROPERTY(EditAnywhere) TObjectPtr<UCapsuleComponent> cartCapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess)) TObjectPtr<UStaticMeshComponent> shoppingCart;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> backWheels;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> frontRightWheel;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> frontLeftWheel;


	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> mapping;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> forward;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> backward;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> steering;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> interact;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> usePowerup;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> useSpecialItem;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> openPlayerList;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, meta = (AllowPrivateAccess)) FString steamUsername;
	//UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SteamUsername) FString steamUsername;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializationDone);
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = True)) FOnInitializationDone onInitializationDone;

	UPROPERTY()EPlayerStatus currentStatus = EPlayerStatus::NONE;
	FTimerHandle timer;
	

public:
	ASeniorPlayer();

public:
	FORCEINLINE TObjectPtr<USeniorMovementComponent> GetSeniorMovementComponent() const { return seniorMovementcomponent; }
	FORCEINLINE TObjectPtr<UCollectedItemComponent> GetCollectedItemComponent() const { return collectedItemComponent; }
	FORCEINLINE TObjectPtr<UCapsuleComponent> GetCartCapsuleComponent()const { return cartCapsuleComponent; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetLeftFrontWheel()const { return frontLeftWheel; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetRightFrontWheel()const { return frontRightWheel; }
	FORCEINLINE TObjectPtr<UPlaceArrowSignComponent> GetPlaceArrowSignComponent() const { return placeArrowSignComponent; }
	FORCEINLINE TObjectPtr<UDestinationArrowComponent> GetDestinationArrowComponent() const { return destinationArrowComponent; }
	FORCEINLINE TObjectPtr<UInventoryComponent> GetInventoryComponent() const { return inventory; }
	FORCEINLINE FString GetSteamUsername() const { return steamUsername; }

	/// <summary>
	/// Custom id replicated, used for network
	/// </summary>
	FORCEINLINE uint32 GetRepActorID()const { return repActorID; }
	/// <summary>
	/// Custom id not replicated, used for network
	/// </summary>
	FORCEINLINE uint32 GetLocalActorID()const { return actorLocalID; }

	void SetMovementActive(bool _isActive);
	

protected:
	virtual void BeginPlay() override;


	/// <summary>
	/// This method is used to notify the game that this player is loaded and ready,
	/// so it's used to know if everybody is ready to start the race
	/// </summary>
	virtual void SendNotifyIsReady();
	void InitUsername();
	void PrintDebug();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// UFUNCTION(Client, Reliable)	void ClientRPC_ReceiveShoppingList(const TArray<ACollectedItem*>& SharedList);
	void SetTemporaryStatus(EPlayerStatus _newStatus, float _duration);
	void ActivateSpeedBoost();
private:
	void InitSubsystem();
	void InitInputs(TObjectPtr<UEnhancedInputComponent> _inputComponent);

private:
	void InitUniqueID();
	UMainWidget* GetMainWidget();
	void ResetStatus();
private:
	UFUNCTION(Server, Reliable) void Server_IncrementCurrentPlayerReady();
	UFUNCTION(Server, Reliable) void Server_ModifySteamUsername(const FString& _steamUsername);
	UFUNCTION(Server, Reliable) void Server_ActivateSpeedBoost();
public:
	UFUNCTION(Client, Reliable) void Client_ApplyMalusEffect(UMaterialInterface* _material, float _duration);
	UFUNCTION(Client, Reliable) void Client_Warning(float _duration);
private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
