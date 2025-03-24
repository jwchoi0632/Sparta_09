// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MultiPlayPrjGameInstance.h"
#include "System/UISubsystem.h"
#include "System/LevelSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "System/MPPlayerController.h"
#include "MyIDPlugin.h"
#include "MyIDPluginBPLibrary.h"

void UMultiPlayPrjGameInstance::Init()
{
	Super::Init();
	
	LevelSubsystem = GetSubsystem<ULevelSubsystem>();
	UISubsystem = GetSubsystem<UUISubsystem>();

	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));

	UISubsystem->InitUISubsystem(this);
}

void UMultiPlayPrjGameInstance::SetPlayerController(AMPPlayerController* NewPlayerController)
{
	PlayerController = NewPlayerController;
	checkf(IsValid(UISubsystem), TEXT("UI Subsystem is invalid"));
	UISubsystem->SetPlayerController(PlayerController);
}

void UMultiPlayPrjGameInstance::QuitGame() const
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}

void UMultiPlayPrjGameInstance::SetUserName(const FName& NewName)
{
	UMyIDPluginBPLibrary::SetUserName(NewName);
}

const FName& UMultiPlayPrjGameInstance::GetUserName() const
{
	return UMyIDPluginBPLibrary::GetUserName();
}

void UMultiPlayPrjGameInstance::MoveLevelInSingle(EMPSceneType SceneType) const
{
	checkf(IsValid(LevelSubsystem), TEXT("LevelSubsystem is invalid"));
	LevelSubsystem->OpenLevelByLevelType(SceneType);
}

void UMultiPlayPrjGameInstance::MoveLevelInMulti(EMPSceneType SceneType) const
{
	checkf(IsValid(LevelSubsystem), TEXT("LevelSubsystem is invalid"));
	LevelSubsystem->OpenLevelByIP();
}

const EMPSceneType UMultiPlayPrjGameInstance::GetCurrentScene() const
{
	checkf(IsValid(LevelSubsystem), TEXT("Level Subsystem is invalid"));
	return LevelSubsystem->GetCurrentLevelType();
}

void UMultiPlayPrjGameInstance::AddUIOfCurrentLevel() const
{
	checkf(IsValid(UISubsystem), TEXT("UI Subsystem is invalid"));
	UISubsystem->AddWidgetToViewportBySceneType(GetCurrentScene());
}

void UMultiPlayPrjGameInstance::RequestAddChatLog(const FText& Message)
{
	checkf(IsValid(PlayerController), TEXT("PlayerController is invalid"));
	PlayerController->SendMessage(UMyIDPluginBPLibrary::GetUserName(), Message);
}

void UMultiPlayPrjGameInstance::ResponseAddUserList(const FName& TargetName)
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->AddUserListToScoreBox(TargetName);
}

void UMultiPlayPrjGameInstance::AddChatLogText(bool bIsLogin, const FName& TargetName, const FText& Message) const
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->PrintChatLogText(bIsLogin, TargetName, Message);
}

const TSharedPtr<SWidget> UMultiPlayPrjGameInstance::GetChatInputBox() const
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	return UISubsystem->GetChatInputBox();
}

void UMultiPlayPrjGameInstance::ResponseStartGame(const FName& TargetName)
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->ApplyStartGame(TargetName == UMyIDPluginBPLibrary::GetUserName());
}

void UMultiPlayPrjGameInstance::OnChangedTurn(const FTurnResultStruct& TurnResult, const FName& TargetName) const
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->AddTurnResultToLogBox(TurnResult, TargetName == UMyIDPluginBPLibrary::GetUserName());
}

void UMultiPlayPrjGameInstance::OnChangedTimer(const int32 TimeValue) const
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->ApplyChangedTime(TimeValue);
}

void UMultiPlayPrjGameInstance::RequestCompareAnswer(const TArray<int32>& Nums) const
{
	checkf(IsValid(PlayerController), TEXT("PlayerController is invalid"));
	PlayerController->SendAnswer(UMyIDPluginBPLibrary::GetUserName(), Nums);
}
void UMultiPlayPrjGameInstance::ResponseNotifyLog(const FText& Notify) const
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->AddGameLogToLogBox(Notify);
}
void UMultiPlayPrjGameInstance::UpdateScore(const FName& TargetName)
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->ApplyScoreOfWinner(TargetName);
}
void UMultiPlayPrjGameInstance::ResponseQuitGame()
{
	MoveLevelInSingle(EMPSceneType::Title);

	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->InitInGameUI();
}
