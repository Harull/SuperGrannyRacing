
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
	onSelected.Broadcast(FName(serverName->Text.ToString()), levelName.GetName(), index);
}

void USessionSlotWidget::InitData(const FSessionData& _data, const int& _index)
{

}