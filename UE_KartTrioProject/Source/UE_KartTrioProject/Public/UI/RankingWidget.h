
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include "RankingWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API URankingWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> rankingList;
	UPROPERTY(EditAnywhere) TSubclassOf<UTextBlock> textRef;
	UPROPERTY() TArray<TObjectPtr<UTextBlock>> allTextBlock;
	
protected:
	virtual void NativeConstruct() override;

public:
	void AddNewPlayerInRanking(const FString& _steamName);

private:
	void DisplayText();
};