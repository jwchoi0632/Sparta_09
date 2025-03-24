// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/MPInGameWidget.h"
#include "UI/Base/Sub/GameLogElementWidget.h"
#include "UI/Base/Sub/ScoreElementWidget.h"
#include "UI/Base/Sub/PlayerInputWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Structure/TurnResultStruct.h"
#include "System/UISubsystem.h"

void UMPInGameWidget::InitWidget(UUISubsystem* NewUISubsystem)
{
	Super::InitWidget(NewUISubsystem);

	PlayerInputBox->InitInputWidget(this);
	PlayerInputBox->SetNotifyVisibility(false);
	PlayerInputBox->SetInputBoxVisibility(false);
}

void UMPInGameWidget::OnStartedGame(const bool bIsTarget)
{
	GameLogBox->ClearChildren();
	FText LogText = FText::FromString(FString::Printf(TEXT("새 게임이 시작되었습니다.")));
	PlayerInputBox->SetNotifyVisibility(true);
	PlayerInputBox->SetNotifyText(LogText);
	AddGameLog(LogText);
	OnChangedTurn(bIsTarget);
}

void UMPInGameWidget::OnChangedTurn(bool bIsTarget)
{
	FText NotifyText = FText::GetEmpty();
	PlayerInputBox->SetInputBoxVisibility(bIsTarget);

	if (bIsTarget)
	{
		NotifyText = FText::FromString(FString::Printf(TEXT("정답을 입력해주세요.")));
	}
	else
	{
		NotifyText = FText::FromString(FString::Printf(TEXT("다른 유저가 풀이 중..")));
	}

	PlayerInputBox->SetNotifyText(NotifyText);
}

void UMPInGameWidget::OnChangedTime(const int32 TimeValue)
{
	PlayerInputBox->SetTimerText(TimeValue);
}

void UMPInGameWidget::NotifyInputComplete(const TArray<int32>& InputNums)
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->RequestCompareAnswer(InputNums);
}

void UMPInGameWidget::AddTurnResult(const FTurnResultStruct& TurnResult)
{
	UGameLogElementWidget* NewResult = CreateWidget<UGameLogElementWidget>(this, GameLogBase.GetClass());

	NewResult->SetElementMode(false);

	NewResult->SetUserName(TurnResult.UserName);
	NewResult->SetResult(TurnResult.Result);
	NewResult->SetStrikeCounter(TurnResult.Strike, TurnResult.Ball);
	NewResult->SetInputNumber(TurnResult.InputNums);

	GameLogBox->AddChild(NewResult);
	GameLogBox->ScrollToEnd();
}

void UMPInGameWidget::AddGameLog(const FText& Message)
{
	UGameLogElementWidget* NewResult = CreateWidget<UGameLogElementWidget>(this, GameLogBase.GetClass());

	NewResult->SetElementMode(true);
	NewResult->SetLogText(Message);

	GameLogBox->AddChild(NewResult);
	GameLogBox->ScrollToEnd();
}

void UMPInGameWidget::AddUserListToScoreBox(const FName& UserName)
{
	int32 RowIndex = UserScoreList.Num();
	UScoreElementWidget* NewUser = CreateWidget<UScoreElementWidget>(this, ScoreBase.GetClass());

	NewUser->InitScore(UserName);
	UserScoreList.Add(UserName, NewUser);
	ListBox->AddChildToUniformGrid(NewUser, RowIndex, 0);
}

void UMPInGameWidget::IncreaseScoreByUserName(const FName& UserName)
{
	if (!UserScoreList.Contains(UserName))
	{
		return;
	}

	UserScoreList[UserName]->IncreaseScore();
}

void UMPInGameWidget::ChangeTargetWidget(TSharedPtr<SWidget> TargetWidget)
{
	if (IsValid(UISubsystem))
	{
		UISubsystem->ApplyChangeTargetWidget(TargetWidget);
	}
}

void UMPInGameWidget::ClearLogs()
{
	PlayerInputBox->SetNotifyVisibility(false);
	PlayerInputBox->SetInputBoxVisibility(false);

	ListBox->ClearChildren();
	GameLogBox->ClearChildren();

	UserScoreList.Empty();
}
