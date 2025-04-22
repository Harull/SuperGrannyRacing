
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinScreenWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UWinScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(Transient, meta = (BindWidgetAnim)) TObjectPtr<UWidgetAnimation> appearAnim;

public:
	virtual void NativeConstruct() override;

public:
	void SetVisible();
};