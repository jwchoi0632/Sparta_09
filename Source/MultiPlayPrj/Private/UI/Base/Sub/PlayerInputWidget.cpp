// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Sub/PlayerInputWidget.h"
#include "UI/Base/MPInGameWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UPlayerInputWidget::InitInputWidget(UMPInGameWidget* NewInGameWidget)
{
	InGameWidget = NewInGameWidget;

	InputBox1->OnTextChanged.AddDynamic(this, &ThisClass::OnChangedInput);
	InputBox2->OnTextChanged.AddDynamic(this, &ThisClass::OnChangedInput);
	InputBox3->OnTextChanged.AddDynamic(this, &ThisClass::OnChangedInput);
}

void UPlayerInputWidget::SetNotifyVisibility(bool bIsVisible)
{
	if (bIsVisible)
	{
		NotifyPanel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NotifyPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayerInputWidget::SetInputBoxVisibility(bool bIsVisible)
{
	if (bIsVisible)
	{
		InitInputBox();
		InputPanel->SetVisibility(ESlateVisibility::Visible);
		RequestChangeTargetWidget(InputBox1->GetCachedWidget());
	}
	else
	{
		InputPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPlayerInputWidget::SetNotifyText(const FText& Notify)
{
	NotifyText->SetText(Notify);
}

void UPlayerInputWidget::SetTimerText(const int32 TimeValue)
{
	TimeText->SetText(FText::FromString(FString::FromInt(TimeValue)));

	if (TimeValue == 0)
	{
		if (InputPanel->GetVisibility() == ESlateVisibility::Visible)
		{
			InGameWidget->NotifyInputComplete(InputNums);
		}
	}
}

void UPlayerInputWidget::OnChangedInput(const FText& ChangeText)
{
	int32 Number = FCString::Atoi(*ChangeText.ToString());

	if (Number <= 0 || Number >= 10 || InputNums.Contains(Number))
	{
		if (TargetIndex == 0)
		{
			InputBox1->SetText(FText::GetEmpty());
		}
		else if (TargetIndex == 1)
		{
			InputBox2->SetText(FText::GetEmpty());
		}
		else if (TargetIndex == 2)
		{
			InputBox3->SetText(FText::GetEmpty());
		}

		return;
	}

	TSharedPtr<SWidget> TargetWidget = nullptr;

	if (TargetIndex == 0)
	{
		InputBox1->SetText(ChangeText);
		InputBox2->SetText(FText::GetEmpty());
		InputBox3->SetText(FText::GetEmpty());

		InputBox1->SetIsReadOnly(true);
		TargetWidget = InputBox2->GetCachedWidget();
	}
	else if (TargetIndex == 1)
	{
		InputBox2->SetText(ChangeText);
		InputBox3->SetText(FText::GetEmpty());

		InputBox2->SetIsReadOnly(true);
		TargetWidget = InputBox3->GetCachedWidget();
	}
	else if (TargetIndex == 2)
	{
		InputBox3->SetIsReadOnly(true);
		TargetWidget = nullptr;
	}

	++TargetIndex;
	InputNums.Add(Number);
	RequestChangeTargetWidget(TargetWidget);
}

void UPlayerInputWidget::RequestChangeTargetWidget(TSharedPtr<SWidget> TargetWidget)
{
	if (!IsValid(InGameWidget))
	{
		return;
	}

	if (TargetWidget == nullptr)
	{
		InGameWidget->NotifyInputComplete(InputNums);
		return;
	}

	InGameWidget->ChangeTargetWidget(TargetWidget);
}

void UPlayerInputWidget::InitInputBox()
{
	TargetIndex = 0;
	InputNums.Empty();

	InputBox1->SetIsReadOnly(false);
	InputBox2->SetIsReadOnly(false);
	InputBox3->SetIsReadOnly(false);

	InputBox1->SetText(FText::GetEmpty());
	InputBox2->SetText(FText::GetEmpty());
	InputBox3->SetText(FText::GetEmpty());
}
