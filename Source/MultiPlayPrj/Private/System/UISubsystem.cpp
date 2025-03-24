// Fill out your copyright notice in the Description page of Project Settings.


#include "System/UISubsystem.h"
#include "System/MultiPlayPrjGameInstance.h"
#include "System/MPPlayerController.h"
#include "System/Settings/UISettings.h"
#include "UI/Base/MPTitleWidget.h"
#include "UI/Base/MPInGameWidget.h"
#include "UI/Cover/MPChatWidget.h"
#include "Structure/TurnResultStruct.h"

void UUISubsystem::InitUISubsystem(UMultiPlayPrjGameInstance* NewGameInstance)
{
	MultiGameInstance = NewGameInstance;

	LoadWidgetClassFromSettings();
}

void UUISubsystem::SetPlayerController(AMPPlayerController* NewPC)
{
	PlayerController = NewPC;
}

TSharedPtr<SWidget> UUISubsystem::GetChatInputBox() const
{
	if (!IsValid(ChatWidget))
	{
		return nullptr;
	}

	if (!bActiveChat)
	{
		return nullptr;
	}

	return ChatWidget->GetTargetWidget();
}

void UUISubsystem::PrintChatLogText(bool bIsLogin, const FName& UserName, const FText& Message)
{
	if (!IsValid(ChatWidget))
	{
		return;
	}

	if (bIsLogin)
	{
		ChatWidget->AddLogToLogBox(UserName);
	}
	else
	{
		ChatWidget->AddChatToLogBox(UserName, Message);
	}
}

void UUISubsystem::RequestSendChat(const FText& Message)
{
	if (!Message.IsEmpty())
	{
		MultiGameInstance->RequestAddChatLog(Message);
	}
	
	ChangeInputMode(FInputModeGameOnly());
}

void UUISubsystem::InitInGameUI()
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->ClearLogs();
	}
}

void UUISubsystem::AddTurnResultToLogBox(const FTurnResultStruct& TurnResult, const bool bIsTarget)
{
	if (IsValid(InGameWidget))
	{
		ChangeInputMode(FInputModeGameOnly());
		InGameWidget->AddTurnResult(TurnResult);

		if (TurnResult.Strike == 3)
		{
			InGameWidget->OnChangedTurn(false);
			FText WinnerText = FText::FromString(FString::Printf(TEXT("%s Win!"), *TurnResult.UserName.ToString()));
			ApplyScoreOfWinner(TurnResult.UserName);
			AddGameLogToLogBox(WinnerText);
		}
		else
		{
			InGameWidget->OnChangedTurn(bIsTarget);
		}
	}
}

void UUISubsystem::AddGameLogToLogBox(const FText& Message)
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->AddGameLog(Message);
	}
}

void UUISubsystem::AddUserListToScoreBox(const FName& UserName)
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->AddUserListToScoreBox(UserName);
	}
}

void UUISubsystem::ApplyScoreOfWinner(const FName& UserName)
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->IncreaseScoreByUserName(UserName);
	}
}

void UUISubsystem::ApplyChangedTime(const int32 TimeValue)
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->OnChangedTime(TimeValue);
	}
}

void UUISubsystem::ApplyStartGame(const bool bIsTarget)
{
	if (IsValid(InGameWidget))
	{
		InGameWidget->OnStartedGame(bIsTarget);
	}
}

void UUISubsystem::RequestCompareAnswer(const TArray<int32>& Nums) const
{
	checkf(IsValid(MultiGameInstance), TEXT("GameInstance is invalid"));
	MultiGameInstance->RequestCompareAnswer(Nums);
}

void UUISubsystem::OnClickedMoveTitle() const
{
	checkf(IsValid(MultiGameInstance), TEXT("GameInstance is invalid"));
	MultiGameInstance->MoveLevelInSingle(EMPSceneType::Title);
}

void UUISubsystem::OnClickedMoveInGame() const
{
	checkf(IsValid(MultiGameInstance), TEXT("GameInstance is invalid"));
	MultiGameInstance->MoveLevelInMulti(EMPSceneType::InGame);
	//MultiGameInstance->MoveLevelInSingle(EMPSceneType::InGame);
}

void UUISubsystem::OnClickedQuitGame() const
{
	checkf(IsValid(MultiGameInstance), TEXT("GameInstance is invalid"));
	MultiGameInstance->QuitGame();
}

void UUISubsystem::ApplyChangeTargetWidget(TSharedPtr<SWidget> TargetWidget)
{
	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(TargetWidget);
	ChangeInputMode(UIInputMode);
}

void UUISubsystem::AddWidgetToViewportBySceneType(const EMPSceneType SceneType)
{
	AddedCount = 0;
	CurrentBase = nullptr;
	CurrentAdded = nullptr;
	bActiveChat = false;

	switch (SceneType)
	{
	case EMPSceneType::Title:
		AddBaseWidgetToViewport(EMPWidgetType::TitleWidget);
		break;

	case EMPSceneType::InGame:
		AddBaseWidgetToViewport(EMPWidgetType::InGameWidget);
		AddCoverWidgetToViewport(EMPWidgetType::ChatWidget);
		break;
	}
}

void UUISubsystem::AddBaseWidgetToViewport(const EMPWidgetType WidgetType)
{
	switch (WidgetType)
	{
	case EMPWidgetType::TitleWidget:
		CheckValidOfTitleWidget();
		CurrentBase = TitleWidget;
		break;

	case EMPWidgetType::InGameWidget:
		CheckValidOfInGameWidget();
		CurrentBase = InGameWidget;
		break;

	default:
		checkNoEntry();
		break;
	}

	CurrentBase->AddToViewport(AddedCount);
	++AddedCount;
}

void UUISubsystem::AddCoverWidgetToViewport(const EMPWidgetType WidgetType)
{
	switch (WidgetType)
	{
	case EMPWidgetType::ChatWidget:
		CheckValidOfChatWidget();
		CurrentAdded = ChatWidget;
		break;

	default:
		checkNoEntry();
		break;
	}

	CurrentAdded->AddToViewport(AddedCount);
	++AddedCount;
}

void UUISubsystem::LoadWidgetClassFromSettings()
{
	const UUISettings* UISettings = GetDefault<UUISettings>();

	checkf(IsValid(UISettings), TEXT("UISettings is invalid"));

	TitleWidgetClass = UISettings->TitleWidgetClass;
	InGameWidgetClass = UISettings->InGameWidgetClass;
	ChatWidgetClass = UISettings->ChatWidgetClass;
}

void UUISubsystem::CheckValidOfChatWidget()
{
	if (!IsValid(ChatWidget))
	{
		checkf(IsValid(ChatWidgetClass), TEXT("ChatWidgetClass is invalid"));
		ChatWidget = CreateWidget<UMPChatWidget>(MultiGameInstance, ChatWidgetClass);
		ChatWidget->InitWidget(this);
	}

	bActiveChat = true;
}

void UUISubsystem::CheckValidOfTitleWidget()
{
	if (!IsValid(TitleWidget))
	{
		checkf(IsValid(TitleWidgetClass), TEXT("TitleWidgetClass is invalid"));
		TitleWidget = CreateWidget<UMPTitleWidget>(MultiGameInstance, TitleWidgetClass);
		TitleWidget->InitWidget(this);
	}

	ChangeInputMode(FInputModeUIOnly());
	ChangeVisibilityMouse(true);
}

void UUISubsystem::CheckValidOfInGameWidget()
{
	if (!IsValid(InGameWidget))
	{
		checkf(IsValid(InGameWidgetClass), TEXT("InGameWidgetClass is invalid"));
		InGameWidget = CreateWidget<UMPInGameWidget>(MultiGameInstance, InGameWidgetClass);
		InGameWidget->InitWidget(this);
	}

	ChangeInputMode(FInputModeGameOnly());
	ChangeVisibilityMouse(false);
}

void UUISubsystem::ChangeInputMode(const FInputModeDataBase& InputMode)
{
	checkf(IsValid(PlayerController), TEXT("PlayerController is invalid"));
	PlayerController->SetInputMode(InputMode);
}

void UUISubsystem::ChangeVisibilityMouse(bool bIsVisible)
{
	checkf(IsValid(PlayerController), TEXT("PlayerController is invalid"));
	PlayerController->SetShowMouseCursor(bIsVisible);
}
