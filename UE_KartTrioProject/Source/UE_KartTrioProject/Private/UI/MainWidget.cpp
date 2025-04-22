
#include "UI/MainWidget.h"
#include "Components/SeniorMovementComponent.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	speed = 0;

	if (playerRef = Cast<ASeniorPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		playerRef->GetSeniorMovementComponent()->OnSpeedUpdate().AddDynamic(this, &UMainWidget::UpdateSpeed);
	}

	InitShoppingList();

	/*FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
		DebugSpeed();
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, true, 1.0f);*/
}

void UMainWidget::InitShoppingList()
{
	TArray<FString> _itemsList = {
		"Banana",
		"Chocolate",
		"Coffee",
		"Diapers"
	};

	for (int _i = 0; _i < 4; _i++)
	{
		TObjectPtr<UItemToCollectWidget> _shopItem = CreateWidget<UItemToCollectWidget>(shoppingList, itemToCollectWidget);
		_shopItem->Construct(_itemsList[_i]);
		_shopItem->Padding.Top = paddingValue;
		_shopItem->Padding.Bottom = paddingValue;
		shoppingList->AddChild(_shopItem);
		_shopItem->AddToViewport();
	}
}

void UMainWidget::UpdateSpeed(float _value)
{
	speed = _value;
	DebugSpeed();
}

void UMainWidget::DebugSpeed()
{
	//speed++;
	FString _adjust = "";
	if (speed < 10)
		_adjust = "00";
	if (speed < 100 && speed >= 10)
		_adjust = "0";
	FText _speedText = FText::FromString(_adjust + FString::FromInt(speed));
	speedDisplayer->SetText(_speedText);
}
