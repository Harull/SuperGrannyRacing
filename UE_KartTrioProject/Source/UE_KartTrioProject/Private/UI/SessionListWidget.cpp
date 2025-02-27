
#include "UI/SessionListWidget.h"

void USessionListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Bind();
	FindSessions();
}

void USessionListWidget::Bind()
{
	createButton->OnClicked.AddDynamic(this, &USessionListWidget::CreateSession);
	refreshButton->OnClicked.AddDynamic(this, &USessionListWidget::OnRefresh);
	startGameButton->OnClicked.AddDynamic(this, &USessionListWidget::OnJoinSession);
}

void USessionListWidget::FindSessions()
{
	if (subsystem = GetSubsystem())
	{
		subsystem->OnSessionsFound().AddDynamic(this, &USessionListWidget::OnSessionsFounds);
		subsystem->FindSessions();
	}
}

void USessionListWidget::ClearSessions()
{
	for (TObjectPtr<UWidget> _widget : sessionList->GetAllChildren())
		_widget->RemoveFromParent();
	allSessions.Empty();
}

TObjectPtr<USessionSlotWidget> USessionListWidget::CreateSessionSlot(const FSessionData& _data, const int& _index)
{
	TObjectPtr<USessionSlotWidget> _sessionSlot = CreateWidget<USessionSlotWidget>(GetWorld(), sessionSlotRef);
	_sessionSlot->InitData(_data, _index);
	allSessions.Add(_sessionSlot);

	return _sessionSlot;
}

void USessionListWidget::RemoveSessionSlot(TObjectPtr<USessionSlotWidget> _slot)
{
	//TODO ?? 
}

void USessionListWidget::CreateSession()
{
	if (!subsystem) return;
	subsystem->CreateSession();
}

void USessionListWidget::OnRefresh()
{
	ClearSessions();
	subsystem->FindSessions();
}

void USessionListWidget::OnSessionsFounds(const TArray<FSessionData>& _datas)
{
	const int32& _dataAmount = _datas.Num();
	for (int _i = 0; _i < _dataAmount; _i++)
	{
		TObjectPtr<USessionSlotWidget> _session = CreateSessionSlot(_datas[_i], _i);
		_session->OnSelected().AddDynamic(this, &USessionListWidget::OnSessionSelected);
		sessionList->AddChild(_session);
	}
}

void USessionListWidget::OnSessionSelected(const FName& _sessionName, const FString& _levelName, const int& _index)
{
	startGameButton->SetIsEnabled(true);
	sessionName = _sessionName;
	levelName = _levelName;
	sessionIndex = _index;
}

void USessionListWidget::OnJoinSession()
{
	GetSubsystem()->JoinSession(sessionName, levelName, sessionIndex);
}