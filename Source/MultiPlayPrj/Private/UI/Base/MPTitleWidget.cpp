// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/MPTitleWidget.h"

void UMPTitleWidget::InitWidget(UUISubsystem* NewUISubsystem)
{
	MoveInGameButton = StartButton;
	QuitGameButton = QuitButton;

	Super::InitWidget(NewUISubsystem);
}
