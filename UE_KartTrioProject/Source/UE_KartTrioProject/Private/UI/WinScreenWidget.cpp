
#include "UI/WinScreenWidget.h"
#include "Animation/WidgetAnimation.h"

void UWinScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	/*FProperty* _prop = GetClass()->PropertyLink;
	
	while (_prop != nullptr)
	{
		if (_prop->GetClass() == FObjectProperty::StaticClass())
		{
			FObjectProperty* _objectProp = Cast<FObjectProperty>(_prop);
			if (_objectProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* _object = _objectProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* _widgetAnim = Cast<UWidgetAnimation>(_object);

				if (_widgetAnim != nullptr)
				{
					appearAnim = _widgetAnim;
				}
			}
		}
		_prop = _prop->PropertyLinkNext;
	}*/

}

void UWinScreenWidget::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
	if (!appearAnim) return;
	PlayAnimation(appearAnim);
}

void UWinScreenWidget::SetText(FText _text)
{
	raceClassement->SetText(_text);
}

void UWinScreenWidget::OnReturnToMenu()
{
	const FString& _menuLevelName = "/Game/Levels/LVL_MainMenu?listen";

	if (GetOwningPlayer()->HasAuthority())
		GetWorld()->ServerTravel(_menuLevelName);
}

void UWinScreenWidget::OnReturnToLobby()
{
	const FString& _lobbyLevelName = "/Game/Levels/LVL_Lobby?listen";

	if (GetOwningPlayer()->HasAuthority())
		GetWorld()->ServerTravel(_lobbyLevelName);
}