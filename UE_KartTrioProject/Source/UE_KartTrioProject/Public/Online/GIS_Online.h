// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Kismet/KismetSystemLibrary.h> // TODO move

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"

#include "GIS_Online.generated.h"

// Macros
#define LOG_C(msg, color) UKismetSystemLibrary::PrintString(this, msg, true, true, color, 20.0f)
#define LOG_CD(msg, color, duration) UKismetSystemLibrary::PrintString(this, msg, true, true, color, duration)
#define LOG(msg, color) LOG_C(msg, FColor::color)
#define IS_LAN(online) online->GetSubsystemName() == "NULL"
#define NUM(value) FString("n") + TEXT("°") + FString::FromInt(value)

USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FString playerName;
	FUniqueNetIdPtr steamID;
	FOnlineUserPresence userPresence;

	FPlayerData() = default;
	FPlayerData(const FString& _playerName, const FUniqueNetIdPtr& _steamId, const FOnlineUserPresence& _userPresence = FOnlineUserPresence())
	{
		playerName = _playerName;
		steamID = _steamId;
		userPresence = _userPresence;
	}
};


USTRUCT()
struct FSessionData
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere) FString sessionName;
	UPROPERTY(VisibleAnywhere) FString serverName;
	UPROPERTY(VisibleAnywhere) FString levelName;
	UPROPERTY(VisibleAnywhere) int32 playersCount; //Ps should be accessed through the GetPlayerCount function
	UPROPERTY(VisibleAnywhere) int32 maxPlayersCount;
	UPROPERTY(VisibleAnywhere) int32 ping;
	UPROPERTY(VisibleAnywhere) TArray<FPlayerData> allPlayersData;

	bool isInitialized = false;

public:
	FSessionData() = default;
	FSessionData(const FOnlineSessionSettings& _settings, const FString& _sessionID = "")
	{
		//settings = _settings;
		_settings.Get(FName("SESSION_NAME"), sessionName);
		_settings.Get(FName("SERVER_NAME"), serverName);
		_settings.Get(FName("LEVEL_NAME"), levelName);
		InitIntValue(_settings, "CURRENT_PLAYERS", playersCount);
		InitIntValue(_settings, "MAX_PLAYERS", maxPlayersCount);
		InitIntValue(_settings, "PING", ping);
		isInitialized = true;
	}

private:
	void InitIntValue(const FOnlineSessionSettings& _settings, const FName& _key, int32& _value)
	{
		FString _valueText;
		_settings.Get(FName(_key), _valueText);
		_value = FCString::Atoi(*_valueText);
	}
public:
	int32 GetPlayerCount(IOnlineSessionPtr _session)
	{
		FOnlineSessionSettings* _settings = _session->GetSessionSettings(FName(sessionName));
		FString _valueText;
		_settings->Get(FName("CURRENT_PLAYERS"), _valueText);
		playersCount = FCString::Atoi(*_valueText);
		return playersCount;
	}
};

UCLASS()
class UE_KARTTRIOPROJECT_API UGIS_Online : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionsFound, const TArray<FSessionData>&, _sessionData);
	UPROPERTY() FOnSessionsFound onSessionsFound;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewSteamUserName, const FString&, _steamName);
	UPROPERTY() FOnNewSteamUserName onNewSteamUserName;

	UPROPERTY(EditAnywhere) int32 maxPlayersCount;
	UPROPERTY(EditAnywhere) FName serverName;
	UPROPERTY(EditAnywhere) FName sessionName;
	UPROPERTY(EditAnywhere) FString levelPath;
	UPROPERTY(EditAnywhere) FString mainMenuLevelPath;
	UPROPERTY(EditAnywhere) FString lobbyLevelPath;
	UPROPERTY(EditAnywhere) FString ipAddress;
	UPROPERTY(EditAnywhere) FString gameSessionID;

	IOnlineSubsystem* online;
	IOnlineSessionPtr session;
	FUniqueNetIdPtr steamID;
	TSharedPtr<FOnlineSessionSettings> sessionSettings;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;
	FSessionData currentSessionData;

	int nonSessionRelatedPlayerCount = 0;

public:
	FORCEINLINE FOnSessionsFound& OnSessionsFound() { return onSessionsFound; }
	FORCEINLINE FOnNewSteamUserName& OnNewSteamUserName() { return onNewSteamUserName; }
	FORCEINLINE FSessionData& GetCurrentSessionData() { return currentSessionData; }
	//FORCEINLINE int GetPlayerCount()
	//{
	//	if (!currentSessionData.isInitialized) return 1;
	//	UKismetSystemLibrary::PrintString(this, "is really searching update player count and stuff", true);
	//	return currentSessionData.GetPlayerCount(session); 
	//}
	FORCEINLINE int GetNonSessionRelatedPlayerCount()const
	{
		return nonSessionRelatedPlayerCount;
	}
	FORCEINLINE void SetNonSessionRelatedPlayerCount(const int _nonSessionRelatedPlayerCount)
	{
		nonSessionRelatedPlayerCount = _nonSessionRelatedPlayerCount;
	}

public:
	UGIS_Online();

public:
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;
	virtual void Deinitialize() override;

private:
	void InitSessionSettings();

protected:
	void OnCreateSessionCompleted(FName _sessionName, bool _wasSuccessful);
	void OnFindSessionCompleted(bool _wasSuccessful);
	void OnJoinSessionCompleted(FName _sessionName, const EOnJoinSessionCompleteResult::Type _result);
	void OnRegisteredCompleted(FName _sessionName, const TArray<FUniqueNetIdRef>& _allIDs, bool _wasSuccessful);
	void OnStartSessionCompleted(FName _sessionName, bool _wasSuccessful);
	void OnUpdateSessionCompleted(FName _sessionName, bool _wasSuccessful);
	void OnEndSessionCompleted(FName _sessionName, bool _wasSuccessful);
	void OnDestroySessionCompleted(FName _sessionName, bool _wasSuccessful);
	void OnSessionFailure(const FUniqueNetId& _id, ESessionFailure::Type _failureType);
	void OnNetworkFailure(UWorld* _world, UNetDriver* _driver, ENetworkFailure::Type _failureType, const FString& _error);
	void OnAcceptInvite(const bool _wasSuccessful, const int32 _controllerId, FUniqueNetIdPtr _userId, const FOnlineSessionSearchResult& _inviteResult);
	void OnParticipantJoined(FName _sessionName, const FUniqueNetId& _participantID);
	void OnParticipantLeft(FName _sessionName, const FUniqueNetId& _participantID, EOnSessionParticipantLeftReason _reason);

public:
	UFUNCTION() void CreateSession();
	UFUNCTION() void UpdateSession();
	UFUNCTION() void FindSessions();
	UFUNCTION() void CancelFindSessions();
	UFUNCTION() void JoinSession(const FName& _sessionName, const FString& _levelPath, const int& _sessionIndex);
	UFUNCTION() void RegisterPlayer();
	UFUNCTION() void StartSession();
	UFUNCTION() void EndSession();
	UFUNCTION() void DestroySession();
	UFUNCTION() FString GetSteamUserName();
};
