
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "LobbyWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerStarted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerStoped);
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> loadingScreenWidget;
	UPROPERTY() FOnTimerStarted onTimerStarted;
	UPROPERTY() FOnTimerStoped onTimerStoped;
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> playersReady;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> maxPlayers;
	UPROPERTY() int playersReadyCount = 0;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> timerToLaunch;

	UPROPERTY() bool timerIsStarted = false;
	UPROPERTY() int timeToLaunchLeft = 3;
	UPROPERTY() float currentTime = 0.0f;
	UPROPERTY() float currentTimeMaxPlayers = 0.0f;
	UPROPERTY() float timeMax = 2.0f;

	FTimerHandle timer;

private:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry&, float _DeltaTime) override;

public:
	UFUNCTION() void UpdatePlayersReady(int _value);

private:
	void IsMaxPlayer();
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	void UpdateTimer(float _value);
	int GetPlayerCount();
};