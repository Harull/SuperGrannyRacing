#include "UI/StatusEffectWidget.h"
#include "SeniorPlayer.h"
#include <Kismet/KismetSystemLibrary.h>

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

	if (UTexture2D* _foundTexture = statusImages[_newStatus])
	{
		statusEffectImage->SetBrushFromTexture(_foundTexture);
		SetVisibility(ESlateVisibility::Visible);
	}

}


void UStatusEffectWidget::HideStatus()
{
    SetVisibility(ESlateVisibility::Hidden);
	
}
