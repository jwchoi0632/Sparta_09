// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Cover/MPChatWidget.h"
#include "System/UISubsystem.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

void UMPChatWidget::InitWidget(UUISubsystem* NewUISubsystem)
{
	Super::InitWidget(NewUISubsystem);

	InputBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnCommittedChatText);
}

TSharedPtr<SWidget> UMPChatWidget::GetTargetWidget()
{
	Super::GetTargetWidget();

	return InputBox->GetCachedWidget();
}

void UMPChatWidget::OnCommittedChatText(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		UISubsystem->RequestSendChat(Text);
		InputBox->SetText(FText::GetEmpty());
		break;

	case ETextCommit::OnCleared:
		//LobbyPlayerController->CompleteChat();
		break;
	}
}

void UMPChatWidget::AddChatToLogBox(const FName& Name, const FText ChatText)
{
	UTextBlock* NewText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	NewText->SetText(FText::FromString(FString::Printf(TEXT("%s : %s"), *Name.ToString(), *ChatText.ToString())));

	LogBox->AddChild(NewText);
	LogBox->ScrollToEnd();
}

void UMPChatWidget::AddLogToLogBox(const FName& Name)
{
	UTextBlock* NewText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	NewText->SetText(FText::FromString(FString::Printf(TEXT("%s 님이 게임에 참여하였습니다."), *Name.ToString())));

	LogBox->AddChild(NewText);
	LogBox->ScrollToEnd();
}
