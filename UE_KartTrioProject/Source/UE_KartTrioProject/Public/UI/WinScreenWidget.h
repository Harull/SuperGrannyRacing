
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "WinScreenWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UWinScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(Transient, meta = (BindWidgetAnim)) TObjectPtr<UWidgetAnimation> appearAnim;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> returnToLobbyButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> returnToMenuButton;

public:
	virtual void NativeConstruct() override;
	void BindButton();
public:
	void SetVisible();
	UFUNCTION() void OnReturnToMenu();
	UFUNCTION() void OnReturnToLobby();

};