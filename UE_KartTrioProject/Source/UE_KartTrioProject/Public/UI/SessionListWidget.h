
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionSlotWidget.h"
#include <Components/ScrollBox.h>
#include "SessionListWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API USessionListWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<USessionSlotWidget> sessionSlotRef;

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> createButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> refreshButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> startGameButton;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UScrollBox> sessionList;

	UPROPERTY() TObjectPtr<UGIS_Online> subsystem;
	UPROPERTY() TArray<TObjectPtr<USessionSlotWidget>> allSessions;

	UPROPERTY() FName sessionName;
	UPROPERTY() FString levelName;
	UPROPERTY() int sessionIndex;

private:
	FORCEINLINE TObjectPtr<UGIS_Online> GetSubsystem() const { return subsystem ? subsystem.Get() : GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>(); }

private:
	virtual void NativeConstruct() override;
	
public:
	void FindSessions();
private:
	void Bind();
	void ClearSessions();
	TObjectPtr<USessionSlotWidget> CreateSessionSlot(const FSessionData& _data, const int& _index);
	void RemoveSessionSlot(TObjectPtr<USessionSlotWidget> _slot);

	UFUNCTION() void CreateSession();
	UFUNCTION() void OnRefresh();
	UFUNCTION() void OnSessionsFounds(const TArray<FSessionData>& _datas);
	UFUNCTION() void OnSessionSelected(const FName& _sessionName, const FString& _levelName, const int& _index);
	UFUNCTION() void OnJoinSession();
};