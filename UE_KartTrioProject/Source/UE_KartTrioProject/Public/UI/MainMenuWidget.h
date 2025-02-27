
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "MainMenuWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> playButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> quitButton;

protected:
	virtual void NativeConstruct() override;
	void BindButton();

private:
	UFUNCTION() void OnPlay();
	UFUNCTION() void OnQuit();
};