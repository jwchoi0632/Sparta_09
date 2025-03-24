// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MPWidgetBase.h"
#include "MPInGameWidget.generated.h"

class UUISubsystem;
class UScrollBox;
class UUniformGridPanel;
class UCanvasPanel;
class UTextBlock;
class UGameLogElementWidget;
class UScoreElementWidget;
class UPlayerInputWidget;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API UMPInGameWidget : public UMPWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UUISubsystem* NewUISubsystem) override;

	void OnStartedGame(const bool bIsTarget);
	void OnChangedTurn(bool bIsTarget);
	void OnChangedTime(const int32 TimeValue);
	void NotifyInputComplete(const TArray<int32>& InputNums);

	void AddTurnResult(const FTurnResultStruct& TurnResult);
	void AddGameLog(const FText& Message);
	
	void AddUserListToScoreBox(const FName& UserName);
	void IncreaseScoreByUserName(const FName& UserName);

	void ChangeTargetWidget(TSharedPtr<SWidget> TargetWidget);

	void ClearLogs();

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> ListBox;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UScrollBox> GameLogBox;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UGameLogElementWidget> GameLogBase;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UScoreElementWidget> ScoreBase;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UPlayerInputWidget> PlayerInputBox;

	TMap<FName, TObjectPtr<UScoreElementWidget>> UserScoreList;
};
