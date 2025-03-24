// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LevelSubsystem.h"
#include "System/MultiPlayPrjGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULevelSubsystem::InitLevelSubsystem(UMultiPlayPrjGameInstance* NewGameInstance)
{
	MultiGameInstance = NewGameInstance;

	
}

void ULevelSubsystem::OpenLevelByLevelType(EMPSceneType LevelType)
{
	CurrentLevelType = LevelType;

	switch (CurrentLevelType)
	{
	case EMPSceneType::Title:
		UGameplayStatics::OpenLevel(GetWorld(), TitleLevelName);
		break;

	case EMPSceneType::InGame:
		UGameplayStatics::OpenLevel(GetWorld(), InGameLevelName);
		break;
	}
}

void ULevelSubsystem::OpenLevelByIP() //const FString& TargetUrl)
{
	CurrentLevelType = EMPSceneType::InGame;
	UGameplayStatics::OpenLevel(GetWorld(), FName("127.0.0.1"));
}

const EMPSceneType ULevelSubsystem::GetCurrentLevelType()
{
	CheckCurrentLevelType();
	return CurrentLevelType;
}

void ULevelSubsystem::CheckCurrentLevelType()
{
	const FString CompareName = GetWorld()->GetMapName();

	if (CompareName.Contains(TitleLevelName.ToString()))
	{
		CurrentLevelType = EMPSceneType::Title;
	}
}
