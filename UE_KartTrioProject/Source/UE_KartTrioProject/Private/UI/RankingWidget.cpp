
#include "UI/RankingWidget.h"
#include <Online/GIS_Online.h>

void URankingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGIS_Online* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>())
	{
		_sub->OnNewSteamUserName().AddDynamic(this, &URankingWidget::AddNewPlayerInRanking);
	}
}

void URankingWidget::AddNewPlayerInRanking(const FString& _steamName)
{
	if (!rankingList) return;
	if (!textRef) return;

	//UTextBlock* _text = CreateWidget<UTextBlock>(rankingList, textRef);
}

void URankingWidget::DisplayText()
{

}