
#include "UI/ItemToCollectWidget.h"

void UItemToCollectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*FTimerHandle _handle;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]()
		{
			CrossItem();
		});
	GetWorld()->GetTimerManager().SetTimer(_handle, _delegate, 5.0f, false, 2.0f);*/
}

void UItemToCollectWidget::Construct(FString _name)
{
	itemName = _name;

	Init();
}

void UItemToCollectWidget::CrossItem()
{
	crossImage->SetVisibility(ESlateVisibility::Visible);
}

void UItemToCollectWidget::Init()
{
	itemNameText->SetText(FText::FromString(itemName));
}