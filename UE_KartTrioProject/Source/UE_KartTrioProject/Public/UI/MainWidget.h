
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <SeniorPlayer.h>
#include "ItemToCollectWidget.h"
#include "WinScreenWidget.h"
#include "UI/UsableItemWidget.h"
#include "UI/ObtainItemWidget.h"
#include "UI/WarningScreenWidget.h"
#include "UI/StatusEffectWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> speedDisplayer;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> shoppingList;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWinScreenWidget> winScreen;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWarningScreenWidget> warningScreen;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UStatusEffectWidget> statusEffectWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UUsableItemWidget> usableItemWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UUsableItemWidget> usableSpecialItemWidget;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UObtainItemWidget> obtainItemWidget;
	UPROPERTY() int speed;

	UPROPERTY() TObjectPtr<ASeniorPlayer> playerRef = nullptr;
	UPROPERTY(EditAnywhere) TSubclassOf<UItemToCollectWidget> itemToCollectWidget = nullptr;
	UPROPERTY() TArray<TObjectPtr<UItemToCollectWidget>> allItemsWidget;

	UPROPERTY() float paddingValue = -10.0f;

public:
	FORCEINLINE TObjectPtr<UUsableItemWidget> GetUsableItemWidget() { return usableItemWidget; }
	FORCEINLINE TObjectPtr<UUsableItemWidget> GetUsableSpecialItemWidget() { return usableSpecialItemWidget; }
	FORCEINLINE TObjectPtr<UObtainItemWidget> GetObtainItemWidget() { return obtainItemWidget; }
	FORCEINLINE TObjectPtr<UWinScreenWidget> GetWinScreenWidget() { return winScreen; }
	FORCEINLINE TObjectPtr<UWarningScreenWidget> GetWarningScreenWidget() { return warningScreen; }
	FORCEINLINE TObjectPtr<UStatusEffectWidget> GetStatusEffectWidget() { return statusEffectWidget; }

protected:
	virtual void NativeConstruct() override;

public:
	TObjectPtr<UItemToCollectWidget> FindItemWidget(FString _name);
	void SetWinScreenVisibility();
	void InitShoppingList(const TArray<TObjectPtr<ACollectedItem>>& _items);

private:
	UFUNCTION() void UpdateSpeed(float _speed);

	void DebugSpeed();	
};
