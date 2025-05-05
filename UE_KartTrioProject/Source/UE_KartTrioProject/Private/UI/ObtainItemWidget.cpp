#include "UI/ObtainItemWidget.h"
#include <Kismet/KismetSystemLibrary.h>

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
	UKismetSystemLibrary::PrintString(this, "Reset");
	if (itemText && itemText->IsValidLowLevel())
	{
		UKismetSystemLibrary::PrintString(this, "Empty", true, true, FLinearColor::Yellow, 2.0f);
		itemText->SetText(FText::GetEmpty());
	}
}
