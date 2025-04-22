
#include "UI/LobbyWidget.h"
#include <Online/GIS_Online.h>

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULobbyWidget::NativeTick(const FGeometry&, float _DeltaTime)
{
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
				GetWorld()->ServerTravel("/Game/Levels/LVL_Base?listen");
				// TODO ServerTravel => GameLevel
			}
		}
	}
}

void ULobbyWidget::UpdatePlayersReady(int _value)
{
	playersReadyCount += _value;
	playersReady->SetText(FText::FromString(FString::FromInt(playersReadyCount)));
	IsMaxPlayer();
}

void ULobbyWidget::IsMaxPlayer()
{
	if (playersReadyCount == 2) // valeur de test
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
