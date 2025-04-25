
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "RankingWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API URankingWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY() TArray<TObjectPtr<UTextBlock>> allTextBlock;
	
protected:
	virtual void NativeConstruct() override;

public:
	void AddNewPlayerInRanking();

private:
	void DisplayText();
};