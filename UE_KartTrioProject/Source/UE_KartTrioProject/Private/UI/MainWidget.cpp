
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

	FTimerHandle _timer;

	GetWorld()->GetTimerManager().SetTimer(_timer, [&]() {UMainWidget::InitShoppingList(); }, 0.1f, false);

	//InitShoppingList();

	/*FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
		DebugSpeed();
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, true, 1.0f);*/
}

void UMainWidget::InitShoppingList()
{

	TArray<TObjectPtr<ACollectedItem>> _allObjects;
	UGIS_CollectedItem* _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_CollectedItem>();
	if (_sub)
	{
		_allObjects = _sub->GetListItem();
		UKismetSystemLibrary::PrintString(this, "ItemList " + FString::FromInt(_sub->GetListItem().Num()));

	}

	const int _count = _allObjects.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		TObjectPtr<UItemToCollectWidget> _shopItem = CreateWidget<UItemToCollectWidget>(shoppingList, itemToCollectWidget);
		_shopItem->Construct(_allObjects[_i]->GetItemName());
		_shopItem->Padding.Top = paddingValue;
		_shopItem->Padding.Bottom = paddingValue;
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
