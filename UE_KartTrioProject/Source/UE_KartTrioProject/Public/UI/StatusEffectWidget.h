#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "StatusEffectWidget.generated.h"

enum class EPlayerStatus;

UCLASS()
class UE_KARTTRIOPROJECT_API UStatusEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UImage> statusEffectImage;
	UPROPERTY(EditAnywhere)TMap<EPlayerStatus, UTexture2D*> statusImages;
public:
	FORCEINLINE TObjectPtr<UImage> GetStatusEffectImage() { return statusEffectImage; }

protected:
	virtual void NativeConstruct() override;
public:
	void UpdateStatus(EPlayerStatus _newStatus);
	void HideStatus();
	
};
