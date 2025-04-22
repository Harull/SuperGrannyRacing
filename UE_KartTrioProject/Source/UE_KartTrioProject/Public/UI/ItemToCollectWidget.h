
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "ItemToCollectWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UItemToCollectWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> itemNameText;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> crossImage;
	UPROPERTY(EditAnywhere) FString itemName = "DEFAULT";
	

public:
	virtual void NativeConstruct() override;
	void Construct(FString _name);
	void CrossItem();

private:
	void Init();

};