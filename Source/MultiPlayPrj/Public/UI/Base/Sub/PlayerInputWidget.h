// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInputWidget.generated.h"

class UMPInGameWidget;
class UEditableTextBox;
class UCanvasPanel;
class UTextBlock;

UCLASS()
class MULTIPLAYPRJ_API UPlayerInputWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitInputWidget(UMPInGameWidget* NewInGameWidget);
	void SetNotifyVisibility(bool bIsVisible);
	void SetInputBoxVisibility(bool bIsVisible);

	void SetNotifyText(const FText& Notify);
	void SetTimerText(const int32 TimeValue);


private:
	UFUNCTION()
	void OnChangedInput(const FText& ChangeText);

	void RequestChangeTargetWidget(TSharedPtr<SWidget> TargetWidget);
	void InitInputBox();

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> NotifyPanel;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> InputPanel;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> NotifyText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputBox1;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputBox2;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputBox3;

	TObjectPtr<UMPInGameWidget> InGameWidget;
	TArray<int32> InputNums;

	int32 TargetIndex = 0;
};
