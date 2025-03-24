// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPWidgetBase.h"
#include "System/UISubsystem.h"
#include "Components/Button.h"

void UMPWidgetBase::InitWidget(UUISubsystem* NewUISubsystem)
{
	UISubsystem = NewUISubsystem;

	if (IsValid(MoveTitleButton))
	{
		MoveTitleButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedMoveTitle);
	}
	
	if (IsValid(MoveInGameButton))
	{
		MoveInGameButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedMoveInGame);
	}
	
	if (IsValid(QuitGameButton))
	{
		QuitGameButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuitGame);
	}
}

TSharedPtr<SWidget> UMPWidgetBase::GetTargetWidget()
{
	return nullptr;
}

void UMPWidgetBase::OnClickedMoveTitle()
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->OnClickedMoveTitle();
}

void UMPWidgetBase::OnClickedQuitGame()
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->OnClickedQuitGame();
}

void UMPWidgetBase::OnClickedMoveInGame()
{
	checkf(IsValid(UISubsystem), TEXT("UISubsystem is invalid"));
	UISubsystem->OnClickedMoveInGame();
}

