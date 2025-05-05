#include "UI/ObtainItemWidget.h"

void UObtainItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UObtainItemWidget::SetText(const FString& _text)
{
	FText _newText = FText::FromString("Reward : " + _text + " can be used !");
	itemText->SetText(_newText);
}

void UObtainItemWidget::ResetText()
{
	if (itemText && itemText->IsValidLowLevel())
	{
		itemText->SetText(FText::GetEmpty());
	}
}
