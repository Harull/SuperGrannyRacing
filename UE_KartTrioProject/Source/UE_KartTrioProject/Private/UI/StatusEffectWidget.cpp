#include "UI/StatusEffectWidget.h"
#include "SeniorPlayer.h"

void UStatusEffectWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStatusEffectWidget::UpdateStatus(EPlayerStatus _newStatus)
{
	if (!statusEffectImage) return;

	if (_newStatus == EPlayerStatus::NONE)
	{
		statusEffectImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (UTexture2D* _foundTexture = statusImages.Contains(_newStatus) ? statusImages[_newStatus] : nullptr)
	{
		statusEffectImage->SetBrushFromTexture(_foundTexture);
		statusEffectImage->SetVisibility(ESlateVisibility::Visible);
	}
}


void UStatusEffectWidget::HideStatus()
{
	if (statusEffectImage)
	{
		statusEffectImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
