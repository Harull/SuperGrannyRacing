
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Online/GIS_Online.h"	
#include "SessionSlotWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API USessionSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSelected, const FName&, _sessionName, const FString&, _level, const int&, _index);
	UPROPERTY() FOnSelected onSelected;
	
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> serverName;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> levelName;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> playersCount;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> ping;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> joinButton;
	UPROPERTY() int index;

public:
	FORCEINLINE FOnSelected& OnSelected() { return onSelected; }

private:
	virtual void NativeConstruct() override;
	void Bind();

	UFUNCTION() void OnJoin();

public:
	void InitData(const FSessionData& _data, const int& _index);

};
