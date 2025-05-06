
#include "UI/LobbyWidget.h"
#include <Online/GIS_Online.h>
#include <Kismet/GameplayStatics.h>
#include <SeniorPlayer.h>
#include <GIS/WS_PlayerClassement.h>

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//GetWorld()->GetTimerManager().SetTimer(timer, [&]() { maxPlayers->SetText(FText::FromString(FString::FromInt(GetPlayerCount()))); }, 0.4f, true);

	//int _maxPLayers = GetWorld()->GetSubsystem<UWS_PlayerClassement>()->GetRange();
	int _maxPLayers = GetPlayerCount();

	maxPlayers->SetText(FText::FromString(FString::FromInt(_maxPLayers)));
}



void ULobbyWidget::NativeTick(const FGeometry&, float _DeltaTime)
{
	currentTimeMaxPlayers += _DeltaTime;

	if (currentTimeMaxPlayers >= 2.f)
	{
		currentTimeMaxPlayers = 0;
		//GetWorld()->GetSubsystem<UWS_PlayerClassement>()->CheckIsPlayerIsNull();
		//int _maxPlayers = GetWorld()->GetSubsystem<UWS_PlayerClassement>()->GetRange();
		int _maxPlayers = GetPlayerCount();
		maxPlayers->SetText(FText::FromString(FString::FromInt(_maxPlayers)));
	}


	if (timerIsStarted)
	{
		currentTime += _DeltaTime;
		UpdateTimer(1 - (currentTime/timeMax));
		if (currentTime >= timeMax)
		{
			currentTime = 0.0f;
			timeToLaunchLeft -= 1;
			timerToLaunch->SetText(FText::FromString(FString::FromInt(timeToLaunchLeft)));
			if (timeToLaunchLeft < 0)
			{
				timerIsStarted = false;
				GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>()->SetNonSessionRelatedPlayerCount(playersReadyCount);

				if (loadingScreenWidget)
				{
					RemoveFromViewport();
					CreateWidget<UUserWidget>(GetWorld(), loadingScreenWidget)->AddToViewport();
				}
				else
					UKismetSystemLibrary::PrintString(this, "ERROR loadingScreenWidget subclassof not set in ULobbyWidget::NativeTick", true, true, FLinearColor::Red);

				if (GetOwningPlayer()->HasAuthority())
					GetWorld()->ServerTravel("/Game/Levels/LVL_Base?listen");
			}
		}
	}
}

void ULobbyWidget::UpdatePlayersReady(int _value)
{
	playersReadyCount += _value;
	if (playersReady)
		playersReady->SetText(FText::FromString(FString::FromInt(playersReadyCount)));
	IsMaxPlayer();
}

void ULobbyWidget::TogglePlayerList()
{
	ESlateVisibility _visibility = listPlayerLobbyWidget->IsVisible() ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	listPlayerLobbyWidget->SetVisibility(_visibility);

	UWS_PlayerClassement* _sub = GetWorld()->GetSubsystem<UWS_PlayerClassement>();
	if (!_sub) return;
	listPlayerLobbyWidget->ClearChildrens();

	TArray<TObjectPtr<UCollectedItemComponent>> _componentsList = _sub->GetAllPlayerCollectedItemComponent();
	for (UCollectedItemComponent* _component : _componentsList)
	{
		AActor* _actor = _component->GetOwner();
		ASeniorPlayer* _player = Cast<ASeniorPlayer>(_actor);
		listPlayerLobbyWidget->AddPlayer(_player, _player->GetSteamUsername());
	}
}

void ULobbyWidget::IsMaxPlayer()
{
	//int _totalPlayerConnected = GetWorld()->GetSubsystem<UWS_PlayerClassement>()->GetRange();
	int _totalPlayerConnected = GetPlayerCount();
	if (playersReadyCount == _totalPlayerConnected) 
	{
		StartTimer();
	}
	else
	{
		StopTimer();
	}
}

void ULobbyWidget::StartTimer()
{
	onTimerStarted.Broadcast();
	timerIsStarted = true;
	timerToLaunch->SetVisibility(ESlateVisibility::Visible);
}

void ULobbyWidget::StopTimer()
{
	if (timerIsStarted)
	{
		onTimerStoped.Broadcast();
		ResetTimer();
	}
}

void ULobbyWidget::ResetTimer()
{
	currentTime = 0.0f;
	timeToLaunchLeft = 3;
	timerToLaunch->SetVisibility(ESlateVisibility::Hidden);
	timerIsStarted = false;
	timerToLaunch->SetText(FText::FromString(FString::FromInt(timeToLaunchLeft)));
}

void ULobbyWidget::UpdateTimer(float _value)
{
	/*FColor _color = FColor(1, 1, 1, _value);
	timerToLaunch->SetColorAndOpacity(FSlateColor(_color));*/
	timerToLaunch->SetOpacity(_value);
}

int ULobbyWidget::GetPlayerCount()
{
	TArray<AActor*> _allActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASeniorPlayer::StaticClass(), _allActors);
	return _allActors.Num();
}
