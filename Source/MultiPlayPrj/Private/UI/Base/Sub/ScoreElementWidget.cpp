// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Sub/ScoreElementWidget.h"
#include "Components/TextBlock.h"

void UScoreElementWidget::InitScore(const FName& UserName)
{
	Score = 0;
	NameText->SetText(FText::FromName(UserName));
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}

void UScoreElementWidget::IncreaseScore()
{
	++Score;
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}
