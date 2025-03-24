// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MPWidgetBase.h"
#include "MPChatWidget.generated.h"

class UUISubsystem;
class UEditableTextBox;
class UScrollBox;

UCLASS()
class MULTIPLAYPRJ_API UMPChatWidget : public UMPWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UUISubsystem* NewUISubsystem) override;
	virtual TSharedPtr<SWidget> GetTargetWidget() override;

	void AddChatToLogBox(const FName& Name, const FText ChatText);
	void AddLogToLogBox(const FName& Name);
	
private:
	UFUNCTION()
	void OnCommittedChatText(const FText& Text, ETextCommit::Type CommitMethod);
	
	

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UScrollBox> LogBox;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputBox;
};
