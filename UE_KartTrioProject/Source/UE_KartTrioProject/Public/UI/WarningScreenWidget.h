#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "WarningScreenWidget.generated.h"


UCLASS()
class UE_KARTTRIOPROJECT_API UWarningScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidgetl)) TObjectPtr<UImage> iconFlash = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> textFlash;
public:
	FORCEINLINE TObjectPtr<UImage> GetWarningIcon() { return iconFlash; }
	FORCEINLINE TObjectPtr<UTextBlock> GetWarningText() { return textFlash; }

protected:
	virtual void NativeConstruct() override;
	
};
