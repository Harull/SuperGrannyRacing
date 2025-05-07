
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/Overlay.h>
#include "SessionListWidget.h"
#include <Components/SizeBox.h>
#include "MainMenuWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> playButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> quitButton;
	//UPROPERTY(meta = (BindWidget)) TObjectPtr<USizeBox> mainMenuSizeBox;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USessionListWidget> sessionListLayout;

protected:
	virtual void NativeConstruct() override;
	void BindButton();

private:
	UFUNCTION() void OnPlay();
	UFUNCTION() void OnQuit();

};