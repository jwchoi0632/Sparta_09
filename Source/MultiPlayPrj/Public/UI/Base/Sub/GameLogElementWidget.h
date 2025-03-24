// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLogElementWidget.generated.h"

class UTextBlock;
class UCanvasPanel;

UCLASS()
class MULTIPLAYPRJ_API UGameLogElementWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUserName(const FName& UserName);
	void SetInputNumber(const TArray<int32>& Nums);
	void SetStrikeCounter(const int32 Strike, const int32 Ball);
	void SetResult(const FText& Result);
	void SetLogText(const FText& Message);
	
	void SetElementMode(bool bIsTextOnly);

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ElementsPanel;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GameLogPanel;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> LogText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> UserNameText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> CountText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> InputText1;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> InputText2;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> InputText3;
};
