
#include "UI/MainWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	speed = 0;

	if (playerRef = Cast<ASeniorPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		playerRef->GetSeniorMovementComponent()->OnSpeedUpdate().AddDynamic(this, &UMainWidget::UpdateSpeed);
	}

	/*FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
		DebugSpeed();
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, true, 1.0f);*/
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
