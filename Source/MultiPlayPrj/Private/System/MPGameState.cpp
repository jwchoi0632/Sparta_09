// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MPGameState.h"
#include "System/MultiPlayPrjGameInstance.h"
#include "System/MPPlayerController.h"
#include "Net/UnrealNetwork.h"

void AMPGameState::InitLocalState(const FName& UserName)
{
	ResponseClientLogin(UserName);
}

void AMPGameState::SendChatMessage(const FName& UserName, const FText& Message)
{
	ResponseMessageLog(UserName, Message);
}

void AMPGameState::AddUserList(const FName& UserName)
{
	ResponseUserList(UserName);
}

void AMPGameState::NotifyGameStart(const FName& UserName)
{
	ResponseGameStarted(UserName);
}

void AMPGameState::NotifyChangedTurn(const FTurnResultStruct& TurnResult, const FName& TargetName)
{
	ResponseEndTurn(TurnResult, TargetName);
}

void AMPGameState::NotifyChangedTime(const int32 TimeValue)
{
	ResponseOnChangedTime(TimeValue);
}

void AMPGameState::SendNotifyMessage(const FText& Notify, bool bIsWin, const FName& UserName)
{
	ResponseNotifyMessage(Notify, bIsWin, UserName);
}

void AMPGameState::QuitAllClients()
{
	ResponseQuit();
}

//void AMPGameState::SetTime(const int32 TimeValue)
//{
//	Time = TimeValue;
//}

void AMPGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMPGameState::ResponseOnChangedTime_Implementation(const int32 TimeValue)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->OnChangedTimer(TimeValue);
}

void AMPGameState::ResponseGameStarted_Implementation(const FName& UserName)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->ResponseStartGame(UserName);
}

void AMPGameState::ResponseUserList_Implementation(const FName& UserName)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->ResponseAddUserList(UserName);
}

void AMPGameState::ResponseEndTurn_Implementation(const FTurnResultStruct& TurnResult, const FName& TargetName)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->OnChangedTurn(TurnResult, TargetName);
}

void AMPGameState::ResponseMessageLog_Implementation(const FName& UserName, const FText& Message)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->AddChatLogText(false, UserName, Message);
}

void AMPGameState::ResponseClientLogin_Implementation(const FName& UserName)
{
	MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	MPPlayerController = GetWorld()->GetFirstPlayerController<AMPPlayerController>();

	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->AddChatLogText(true, UserName);
}

//void AMPGameState::OnRep_Timer()
//{
//	if (HasAuthority())
//	{
//		return;
//	}
//	
//	if (!IsValid(MPGameInstance))
//	{
//		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
//	}
//
//	MPGameInstance->OnChangedTimer(Time);
//}

void AMPGameState::ResponseNotifyMessage_Implementation(const FText& Notify, bool bIsWin, const FName& UserName)
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->ResponseNotifyLog(Notify);

	if (bIsWin)
	{
		MPGameInstance->UpdateScore(UserName);
	}
}

void AMPGameState::ResponseQuit_Implementation()
{
	if (HasAuthority())
	{
		return;
	}

	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}

	MPGameInstance->ResponseQuitGame();
}
