
#include "UI/MainWidget.h"
#include "Components/SeniorMovementComponent.h"
#include <GIS/GIS_CollectedItem.h>
#include <Kismet/KismetSystemLibrary.h>

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	speed = 0;

	if (playerRef = Cast<ASeniorPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		playerRef->GetSeniorMovementComponent()->OnSpeedUpdate().AddDynamic(this, &UMainWidget::UpdateSpeed);
	}

	//InitShoppingList();

	/*FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
		DebugSpeed();
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, true, 1.0f);*/
}

void UMainWidget::InitShoppingList(const TArray<TObjectPtr<ACollectedItem>>& Items)
{
	shoppingList->ClearChildren();
	allItemsWidget.Empty();

	const int _count = Items.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		TObjectPtr<UItemToCollectWidget> _shopItem = CreateWidget<UItemToCollectWidget>(this, itemToCollectWidget);
		_shopItem->Construct(Items[_i]->GetItemName());
		//_shopItem->Padding.Top = paddingValue;
		//_shopItem->Padding.Bottom = paddingValue;
		shoppingList->AddChild(_shopItem);
		_shopItem->AddToViewport();
		allItemsWidget.Add(_shopItem);
	}
}

TObjectPtr<UItemToCollectWidget> UMainWidget::FindItemWidget(FString _name)
{
	int _count = allItemsWidget.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		if (allItemsWidget[_i]->GetItemName() == _name)
		{
			return allItemsWidget[_i];
		}
	}

	return nullptr;
}

void UMainWidget::SetWinScreenVisibility()
{
	winScreen->SetVisible();
}

void UMainWidget::UpdateSpeed(float _speed)
{
	speed = FMath::Abs(_speed);
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
