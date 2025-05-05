#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "ObtainItemWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UObtainItemWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> itemText;

public:
	FORCEINLINE TObjectPtr<UTextBlock> GetText()const { return itemText; }

private:
	virtual void NativeConstruct() override;

public:
	void SetText(const FString& _text);
	void ResetText();
	
};
