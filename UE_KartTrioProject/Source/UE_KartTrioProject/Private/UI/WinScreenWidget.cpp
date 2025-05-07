
#include "UI/WinScreenWidget.h"
#include "Animation/WidgetAnimation.h"
#include <Kismet/KismetSystemLibrary.h>
#include <SeniorPlayer.h>
#include <Kismet/GameplayStatics.h>

void UWinScreenWidget::NativeConstruct()
{
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
	BindButton();

	GetOwningPlayer()->HasAuthority() ? returnToLobbyButton->SetVisibility(ESlateVisibility::Visible) : returnToLobbyButton->SetVisibility(ESlateVisibility::Hidden);
}

void UWinScreenWidget::BindButton()
{
	returnToLobbyButton->OnClicked.AddDynamic(this, &UWinScreenWidget::OnReturnToLobby);
	returnToMenuButton->OnClicked.AddDynamic(this, &UWinScreenWidget::OnReturnToMenu);
}

void UWinScreenWidget::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
	if (!appearAnim) return;
	PlayAnimation(appearAnim);
}

void UWinScreenWidget::OnReturnToMenu()
{
	const FString _menuLevelName = "/Game/Levels/LVL_MainMenu?listen";

	if (GetOwningPlayer()->HasAuthority())
		GetWorld()->ServerTravel(_menuLevelName);
	else
		UGameplayStatics::OpenLevel(this, FName(_menuLevelName), true);
}

void UWinScreenWidget::OnReturnToLobby()
{
	const FString _lobbyLevelName = "/Game/Levels/LVL_Lobby?listen";

	if (GetOwningPlayer()->HasAuthority())
		GetWorld()->ServerTravel(_lobbyLevelName);
}

//void UWinScreenWidget::OnReturnToLobby()
//{
//	const FString _lobbyLevelName = "/Game/Levels/LVL_Lobby?listen";
//
//	if (GetOwningPlayer()->HasAuthority())
//		GetWorld()->ServerTravel("/Game/Levels/LVL_Lobby?listen");
//}

