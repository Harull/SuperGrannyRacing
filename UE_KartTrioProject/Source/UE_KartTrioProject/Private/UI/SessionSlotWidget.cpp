
#include "UI/SessionSlotWidget.h"

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Bind();
}

void USessionSlotWidget::Bind()
{
	if (!joinButton) return;

	joinButton->OnClicked.AddDynamic(this, &USessionSlotWidget::OnJoin);
}

void USessionSlotWidget::OnJoin()
{
	//LOG("CLICKED", White);
	onSelected.Broadcast(FName(sessionName), levelName.GetName(), index);
}

void USessionSlotWidget::InitData(const FSessionData& _data, const int& _index)
{
	sessionName = _data.sessionName;
	serverName->SetText(FText::FromString(_data.serverName));
	levelName->SetText(FText::FromString(_data.levelName));
	FText _playersCount = FText::FromString(FString::FromInt(_data.playersCount) + " / " + FString::FromInt(_data.maxPlayersCount));
	playersCount->SetText(_playersCount);
	ping->SetText(FText::FromString(FString::FromInt(_data.ping) + "ms"));		
}