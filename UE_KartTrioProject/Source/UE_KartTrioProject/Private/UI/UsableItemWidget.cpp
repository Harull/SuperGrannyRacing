#include "UI/UsableItemWidget.h"
#include "GPE/Item.h"
#include <Kismet/KismetSystemLibrary.h>

void UUsableItemWidget::SetItemImage(TObjectPtr<UImage> _image, UTexture2D* _newImage)
{
	if (_image)
		_image->SetBrushFromTexture(_newImage, true);
}

void UUsableItemWidget::UpdateItemsImage(const TArray<TSubclassOf<AItem>>& _items)
{
	itemAvailableImage->SetBrushFromTexture(nullptr);
	int _count = _items.Num();

	for (int i = 0; i < _count; i++)
	{
		AItem* _temp = GetWorld()->SpawnActor<AItem>(_items[i]);
		if (!_temp)continue;

		itemAvailableImage->SetBrushFromTexture(_temp->GetItemImage());

		_temp->Destroy();
	}
}

void UUsableItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
