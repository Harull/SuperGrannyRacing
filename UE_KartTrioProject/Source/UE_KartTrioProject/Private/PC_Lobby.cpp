
#include "PC_Lobby.h"
#include <Online/GIS_Online.h>

void APC_Lobby::BeginPlay()
{
	Super::BeginPlay();

	if (this != GetWorld()->GetFirstPlayerController())
		return;

	FTimerHandle _timer;
	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {
			if (TObjectPtr<UGIS_Online> _online = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>())
			{
				if (HasAuthority())
				{
					_online->CreateSession();
				}
			}
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, false);
}
