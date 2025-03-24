// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "System/MPTypes.h"
#include "UISubsystem.generated.h"

class UMultiPlayPrjGameInstance;
class UMPWidgetBase;
class UMPTitleWidget;
class UMPInGameWidget;
class UMPChatWidget;
class AMPPlayerController;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void InitUISubsystem(UMultiPlayPrjGameInstance* NewGameInstance);
	void SetPlayerController(AMPPlayerController* NewPC);

	void AddWidgetToViewportBySceneType(const EMPSceneType SceneType);
	void AddBaseWidgetToViewport(const EMPWidgetType WidgetType);
	void AddCoverWidgetToViewport(const EMPWidgetType WidgetType);

	TSharedPtr<SWidget> GetChatInputBox() const;

	void PrintChatLogText(bool bIsLogin, const FName& UserName, const FText& Message = FText::GetEmpty());
	void RequestSendChat(const FText& Message);

	void InitInGameUI();
	void AddTurnResultToLogBox(const FTurnResultStruct& TurnResult, const bool bIsTarget);
	void AddGameLogToLogBox(const FText& Message);
	void AddUserListToScoreBox(const FName& UserName);
	void ApplyScoreOfWinner(const FName& UserName);
	void ApplyChangedTime(const int32 TimeValue);

	void ApplyStartGame(const bool bIsTarget);
	void RequestCompareAnswer(const TArray<int32>& Nums) const;

	void OnClickedMoveTitle() const;
	void OnClickedMoveInGame() const;
	void OnClickedQuitGame() const;

	void ApplyChangeTargetWidget(TSharedPtr<SWidget> TargetWidget);

private:
	void LoadWidgetClassFromSettings();

	void CheckValidOfTitleWidget();
	void CheckValidOfInGameWidget();
	void CheckValidOfChatWidget();

	void ChangeInputMode(const FInputModeDataBase& InputMode);
	void ChangeVisibilityMouse(bool bIsVisible);

private:
	UPROPERTY()
	TObjectPtr<UMultiPlayPrjGameInstance> MultiGameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<AMPPlayerController> PlayerController = nullptr;

	UPROPERTY()
	TSubclassOf<UMPTitleWidget> TitleWidgetClass = nullptr;

	UPROPERTY()
	TSubclassOf<UMPInGameWidget> InGameWidgetClass = nullptr;

	UPROPERTY()
	TSubclassOf<UMPChatWidget> ChatWidgetClass = nullptr;


	UPROPERTY()
	TObjectPtr<UMPTitleWidget> TitleWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UMPInGameWidget> InGameWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UMPChatWidget> ChatWidget = nullptr;


	UPROPERTY()
	TObjectPtr<UMPWidgetBase> CurrentBase = nullptr;

	UPROPERTY()
	TObjectPtr<UMPWidgetBase> CurrentAdded = nullptr;

	bool bActiveChat = false;
	int32 AddedCount = 0;
};
