// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreElementWidget.generated.h"

class UTextBlock;

UCLASS()
class MULTIPLAYPRJ_API UScoreElementWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitScore(const FName& UserName);
	void IncreaseScore();
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	int32 Score = 0;
};
