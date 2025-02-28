// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/GIS_Online.h"

UGIS_Online::UGIS_Online()
{
	maxPlayersCount = 12;
	serverName = "GIS_Name";
	sessionName = "Unknown";
	levelPath = "Unknown";
	mainMenuLevelPath = "LVL_MainMenu";
	lobbyLevelPath = "LVL_Lobby";
	ipAddress = "Unknown";
	online = nullptr;
	session = nullptr;
	steamID = nullptr;
	sessionSettings = MakeShareable(new FOnlineSessionSettings());
}

void UGIS_Online::Initialize(FSubsystemCollectionBase& _collection)
{
	online = IOnlineSubsystem::Get();
	if (!online)
	{
		LOG("Error => Online cannot be instanced!", Red);
		return;
	}

	LOG("You are now online on " + online->GetSubsystemName().ToString() + "!", Green);

	session = online->GetSessionInterface();
	if (session)
	{
		session->OnCreateSessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnCreateSessionCompleted);
		session->OnFindSessionsCompleteDelegates.AddUObject(this, &UGIS_Online::OnFindSessionCompleted);
		session->OnJoinSessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnJoinSessionCompleted);
		session->OnRegisterPlayersCompleteDelegates.AddUObject(this, &UGIS_Online::OnRegisteredCompleted);
		session->OnStartSessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnStartSessionCompleted);
		session->OnUpdateSessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnUpdateSessionCompleted);
		session->OnEndSessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnEndSessionCompleted);
		session->OnDestroySessionCompleteDelegates.AddUObject(this, &UGIS_Online::OnDestroySessionCompleted);

		session->OnSessionFailureDelegates.AddUObject(this, &UGIS_Online::OnSessionFailure);
		GEngine->OnNetworkFailure().AddUObject(this, &UGIS_Online::OnNetworkFailure);
	}

	if (IOnlineIdentityPtr _interface = online->GetIdentityInterface())
	{
		steamID = _interface->GetUniquePlayerId(0);
	}
}

void UGIS_Online::Deinitialize()
{
	LOG("UGIS_Online => Deinitialize", Red);
}

void UGIS_Online::InitSessionSettings()
{
	if (!sessionSettings)
		return;
	sessionSettings->bAllowInvites = true;
	sessionSettings->bAllowJoinInProgress = true;
	sessionSettings->bAllowJoinViaPresence = true;
	sessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
	sessionSettings->bIsDedicated = false;
	sessionSettings->bUseLobbiesIfAvailable = true;
	sessionSettings->bUsesPresence = true;
	sessionSettings->bShouldAdvertise = true;
	sessionSettings->NumPrivateConnections = 0;
	sessionSettings->NumPublicConnections = maxPlayersCount;
	sessionSettings->bIsLANMatch = IS_LAN(online);

	sessionSettings->Set(FName("SERVER_NAME"), serverName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings->Set(FName("LEVEL_NAME"), levelPath, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings->Set(FName("CURRENT_PLAYERS"), FString::FromInt(1), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings->Set(FName("MAX_PLAYERS"), FString::FromInt(4), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings->Set(FName("PING_PLAYERS"), FString::FromInt(8), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
}

#pragma region Handlers

void UGIS_Online::OnCreateSessionCompleted(FName _sessionName, bool _wasSuccessful)
{
	if (!_wasSuccessful)
	{
		LOG("Error => " + _sessionName.ToString() + " wasn't created successfully!", Red);
		return;
	}
	sessionName = _sessionName;
	RegisterPlayer();
}

void UGIS_Online::OnFindSessionCompleted(bool _wasSuccessful)
{
	LOG("UGIS_Online => OnFindSessionCompleted", Green);

	if (!_wasSuccessful)
	{
		LOG("Error => The session search has failed!", Red);
		return;
	}
	if (!sessionSearch)
		return;
	const TArray<FOnlineSessionSearchResult> _results = sessionSearch->SearchResults;
	const int32& _resultsCount = _results.Num();
	if (_resultsCount <= 0)
	{
		LOG("Error => No session found!", Red);
		return;
	}
	TArray<FSessionData> _sessionsData;
	for (FOnlineSessionSearchResult _result : _results)
	{
		if (!_result.IsValid())
			continue;
		const FSessionData& _data = FSessionData(_result.Session.SessionSettings);
		LOG("SessionData => " + _data.serverName, Green);
		_sessionsData.Add(_data);
	}
	onSessionsFound.Broadcast(_sessionsData);
}

void UGIS_Online::OnJoinSessionCompleted(FName _sessionName, const EOnJoinSessionCompleteResult::Type _result)
{
	LOG("UGIS_Online => OnJoinSessionCompleted", Green);

	if (_result != EOnJoinSessionCompleteResult::Success)
	{
		LOG("Error => " + FString(LexToString(_result)) + "!", Red);
		return;
	}
	sessionName = _sessionName;
	session->GetResolvedConnectString(sessionName, ipAddress);
	if (APlayerController* _playerController = GetGameInstance()->GetFirstLocalPlayerController())
	{
		LOG("The client travels on the server: " + levelPath + "!", Green);
		_playerController->ClientTravel(ipAddress, ETravelType::TRAVEL_Absolute, false);
	}
}

void UGIS_Online::OnRegisteredCompleted(FName _sessionName, const TArray<FUniqueNetIdRef>& _allIDs, bool _wasSuccessful)
{
	if (!_wasSuccessful)
	{
		LOG("Error => The registration failed!", Red);
		return;
	}

	sessionName = _sessionName;
	for (const FUniqueNetIdRef& _netIdRef : _allIDs)
	{
		const FUniqueNetId& _netId = _netIdRef.Get();
		const FString& _playerName = online->GetIdentityInterface()->GetPlayerNickname(_netId);

		if (IOnlinePresencePtr _sessionPresence = online->GetPresenceInterface())
		{
			TSharedPtr<FOnlineUserPresence> _userPresence;

			if (_sessionPresence->GetCachedPresence(_netId, _userPresence) == EOnlineCachedResult::Success)
			{
				const FPlayerData& _playerData = FPlayerData(_playerName, steamID, *_userPresence);
				// TODO broadcast
			}
		}
		else
		{
			const FPlayerData& _playerData = FPlayerData(_playerName, steamID);
		}
	}
}

void UGIS_Online::OnStartSessionCompleted(FName _sessionName, bool _wasSuccessful)
{
	LOG("UGIS_Online => OnStartSessionCompleted", Green);

	if (!_wasSuccessful)
	{
		LOG("Error => Start session failed!", Red);
		return;
	}
	sessionName = _sessionName;
	LOG("Session => \"" + sessionName.ToString() + "\" started!", Green);
	GetWorld()->ServerTravel("/Game/Levels/" + levelPath + "?listen");
}

void UGIS_Online::OnUpdateSessionCompleted(FName _sessionName, bool _wasSuccessful)
{
	LOG("UGIS_Online => OnUpdateSessionCompleted", Green);
}

void UGIS_Online::OnEndSessionCompleted(FName _sessionName, bool _wasSuccessful)
{
	LOG("UGIS_Online => OnEndSessionCompleted", Green);

	if (!_wasSuccessful)
	{
		LOG("Error => End session failed!", Red);
		return;
	}
	GetWorld()->ServerTravel("/Game/Levels/" + lobbyLevelPath + "?listen");
}

void UGIS_Online::OnDestroySessionCompleted(FName _sessionName, bool _wasSuccessful)
{
	LOG("UGIS_Online => OnDestroySessionCompleted", Green);

	if (!_wasSuccessful)
	{
		LOG("Error => Destroy session failed!", Red);
		return;
	}
	GetWorld()->ServerTravel("/Game/Levels/" + mainMenuLevelPath + "?listen");
}

void UGIS_Online::OnSessionFailure(const FUniqueNetId& _id, ESessionFailure::Type _failureType)
{
	LOG("Error => Session failure!", Red);
}

void UGIS_Online::OnNetworkFailure(UWorld* _world, UNetDriver* _driver, ENetworkFailure::Type _failureType, const FString& _error)
{
	LOG("Error => " + _error + " (" + ENetworkFailure::ToString(_failureType) + ")!", Red);
}

#pragma endregion

#pragma region Callables
void UGIS_Online::CreateSession()
{
	LOG("UGIS_Online => CreateSession", Magenta);
	sessionName = FName(serverName.ToString() + "_" + steamID->ToString());
	if (session->GetNamedSession(sessionName))
	{
		DestroySession();
		return;
	}

	InitSessionSettings();
	session->CreateSession(0, sessionName, *sessionSettings.Get());
}

void UGIS_Online::UpdateSession()
{
	LOG("UGIS_Online => UpdateSession", Magenta);
	FOnlineSessionSettings _newSettings = *sessionSettings.Get();
	session->UpdateSession(sessionName, _newSettings);
	sessionSettings = MakeShared<FOnlineSessionSettings>(_newSettings);
}

void UGIS_Online::FindSessions()
{
	LOG("UGIS_Online => FindSessions", Magenta);

	if (serverName.IsNone())
		return;
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	sessionSearch->bIsLanQuery = IS_LAN(online);
	sessionSearch->MaxSearchResults = 10;
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	session->FindSessions(0, sessionSearch.ToSharedRef());
}

void UGIS_Online::CancelFindSessions()
{
	LOG("UGIS_Online => CancelFindSessions", Magenta);
	session->CancelFindSessions();
}

void UGIS_Online::JoinSession(const FName& _sessionName, const FString& _levelPath, const int& _sessionIndex)
{
	LOG("UGIS_Online => JoinSession", Magenta);
	sessionName = _sessionName;
	levelPath = _levelPath;

	const TArray<FOnlineSessionSearchResult>& _result = sessionSearch->SearchResults;
	if (_sessionIndex < 0 || _sessionIndex >= _result.Num())
	{
		LOG("Error => Impossible to join the session " + NUM(_sessionIndex) + "!", Red);
		return;
	}

	session->JoinSession(0, sessionName, _result[_sessionIndex]);
}

void UGIS_Online::RegisterPlayer()
{
	if (!steamID)
	{
		LOG("UGIS_Online => RegisterPlayer failed! " + steamID->ToString(), Red);
		return;
	}
	session->RegisterPlayer(sessionName, *steamID, false); // TODO modify on invite
}

void UGIS_Online::StartSession()
{
	LOG("UGIS_Online => StartSession", Magenta);
	session->StartSession(sessionName);
}

void UGIS_Online::EndSession()
{
	LOG("UGIS_Online => EndSession", Magenta);
	session->EndSession(sessionName);
}

void UGIS_Online::DestroySession()
{
	LOG("UGIS_Online => DestroySession", Magenta);
	session->DestroySession(sessionName);
}
#pragma endregion