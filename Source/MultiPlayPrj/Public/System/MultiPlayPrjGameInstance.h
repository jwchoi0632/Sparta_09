// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "System/MPTypes.h"
#include "MultiPlayPrjGameInstance.generated.h"

class UUISubsystem;
class ULevelSubsystem;
class AMPPlayerController;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API UMultiPlayPrjGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	// Game Controll
	void SetPlayerController(AMPPlayerController* NewPlayerController);
	void QuitGame() const;

	// User Data Controll
	void SetUserName(const FName& NewName);
	const FName& GetUserName() const;

	// Level Controll
	void MoveLevelInSingle(EMPSceneType SceneType) const;
	void MoveLevelInMulti(EMPSceneType SceneType) const;
	const EMPSceneType GetCurrentScene() const;

	// UI Controll
	void AddUIOfCurrentLevel() const;
	void RequestAddChatLog(const FText& Message);
	void ResponseAddUserList(const FName& TargetName);
	void AddChatLogText(bool bIsLogin, const FName& TargetName, const FText& Message = FText::GetEmpty()) const;
	const TSharedPtr<SWidget> GetChatInputBox() const;

	void ResponseStartGame(const FName& TargetName);
	void OnChangedTurn(const FTurnResultStruct& TurnResult, const FName& TargetName) const;
	void OnChangedTimer(const int32 TimeValue) const;
	void RequestCompareAnswer(const TArray<int32>& Nums) const;
	void ResponseNotifyLog(const FText& Notify) const;
	void UpdateScore(const FName& TargetName);
	void ResponseQuitGame();
	

private:
	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem = nullptr;

	UPROPERTY()
	TObjectPtr<ULevelSubsystem> LevelSubsystem = nullptr;

	UPROPERTY()
	TObjectPtr<AMPPlayerController> PlayerController = nullptr;
};
