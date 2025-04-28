
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <SeniorPlayer.h>
#include "ItemToCollectWidget.h"
#include "WinScreenWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> speedDisplayer;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> shoppingList;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UWinScreenWidget> winScreen;
	UPROPERTY() int speed;

	UPROPERTY() TObjectPtr<ASeniorPlayer> playerRef = nullptr;
	UPROPERTY(EditAnywhere) TSubclassOf<UItemToCollectWidget> itemToCollectWidget = nullptr;
	UPROPERTY() TArray<TObjectPtr<UItemToCollectWidget>> allItemsWidget;

	UPROPERTY() float paddingValue = -10.0f;

protected:
	virtual void NativeConstruct() override;
	void InitShoppingList();

public:
	TObjectPtr<UItemToCollectWidget> FindItemWidget(FString _name);
	void SetWinScreenVisibility();

private:
	UFUNCTION() void UpdateSpeed(float _speed);

	void DebugSpeed();	
};
