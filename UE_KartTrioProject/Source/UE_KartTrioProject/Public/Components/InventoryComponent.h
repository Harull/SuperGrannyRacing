#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include<InputActionValue.h>
#include "InventoryComponent.generated.h"

class AItem;
class ASeniorPlayer;
class UMainWidget;
class UUsableItemWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_KARTTRIOPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUse, TSubclassOf<AItem>, _item, ASeniorPlayer*, _player, FVector, _pos);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartAnim);
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUse, TSubclassOf<AItem>, _item, FTransform, _transform);
	UPROPERTY() FOnUse onUse;
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta = (AllowPrivateAccess)) FOnStartAnim onStartAnim;

	UPROPERTY(EditAnywhere)bool canUse = true;
	UPROPERTY(EditAnywhere)bool canUseSpecialItem = true;
	UPROPERTY(EditAnywhere) int maxCount = 1;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AItem>> items;
	UPROPERTY(EditAnywhere) TSubclassOf<AItem> specialItem;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AItem>> rewardItems;


public:
	FORCEINLINE FOnUse& OnUse() { return onUse; }
	FORCEINLINE int GetMaxCount()const { return maxCount; }
	FORCEINLINE bool GetCanUse() { return canUse; }

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddItem(TSubclassOf<AItem> _item);
	UFUNCTION() void UseItem(const FInputActionValue& _value);
	UFUNCTION(BlueprintCallable) void UseSpecialItem();
	UFUNCTION() void StartAnimSpecialItem(const FInputActionValue& _value);
	void Reward();

private:
	UMainWidget* GetMainWidget()const;
	void UpdateItemIcon();
	void ToggleText();

		
};
