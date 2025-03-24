// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Sub/GameLogElementWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UGameLogElementWidget::SetUserName(const FName& UserName)
{
	UserNameText->SetText(FText::FromName(UserName));
}

void UGameLogElementWidget::SetInputNumber(const TArray<int32>& Nums)
{
	TArray<int32> Temp;
	Temp.Init(0, 3);

	if (!Nums.IsEmpty())
	{
		for (int32 i = 0; i < Nums.Num(); i++)
		{
			Temp[i] = Nums[i];
		}
	}

	InputText1->SetText(FText::FromString(FString::FromInt(Temp[0])));
	InputText2->SetText(FText::FromString(FString::FromInt(Temp[1])));
	InputText3->SetText(FText::FromString(FString::FromInt(Temp[2])));
}

void UGameLogElementWidget::SetStrikeCounter(const int32 Strike, const int32 Ball)
{
	CountText->SetText(FText::FromString(FString::Printf(TEXT("%d S  %d B"), Strike, Ball)));
}

void UGameLogElementWidget::SetResult(const FText& Result)
{
	ResultText->SetText(Result);
}

void UGameLogElementWidget::SetLogText(const FText& Message)
{
	LogText->SetText(Message);
}

void UGameLogElementWidget::SetElementMode(bool bIsTextOnly)
{
	if (bIsTextOnly)
	{
		ElementsPanel->SetVisibility(ESlateVisibility::Collapsed);
		GameLogPanel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ElementsPanel->SetVisibility(ESlateVisibility::Visible);
		GameLogPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}
