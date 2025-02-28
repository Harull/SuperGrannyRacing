
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <SeniorPlayer.h>
#include "MainWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> speedDisplayer;
	UPROPERTY() int speed;

	UPROPERTY() TObjectPtr<ASeniorPlayer> playerRef = nullptr;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION() void UpdateSpeed(float _value);

	void DebugSpeed();	
};