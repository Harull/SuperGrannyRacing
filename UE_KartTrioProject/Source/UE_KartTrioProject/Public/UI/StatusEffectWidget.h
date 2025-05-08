#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "StatusEffectWidget.generated.h"

UCLASS()
class UE_KARTTRIOPROJECT_API UStatusEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UImage> statusEffectImage;
public:
	FORCEINLINE TObjectPtr<UImage> GetStatusEffectImage() { return statusEffectImage; }

protected:
	virtual void NativeConstruct() override;
	
};
