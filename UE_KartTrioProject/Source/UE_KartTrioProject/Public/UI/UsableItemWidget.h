#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "UsableItemWidget.generated.h"


class AItem;

UCLASS()
class UE_KARTTRIOPROJECT_API UUsableItemWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional)) TObjectPtr<UImage> itemAvailableImage = nullptr;

public:
	void SetItemImage(TObjectPtr<UImage> _image, UTexture2D* _newImage);
	void UpdateItemsDashboard(const TArray<TSubclassOf<AItem>>& _items);

private:
	virtual void NativeConstruct() override;
	
};
