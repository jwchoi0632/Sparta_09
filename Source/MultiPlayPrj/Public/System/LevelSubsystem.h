// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "System/MPTypes.h"
#include "LevelSubsystem.generated.h"

class UMultiPlayPrjGameInstance;

UCLASS()
class MULTIPLAYPRJ_API ULevelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void InitLevelSubsystem(UMultiPlayPrjGameInstance* NewGameInstance);

	void OpenLevelByLevelType(EMPSceneType LevelType);
	void OpenLevelByIP(); //const FString& TargetUrl);
	const EMPSceneType GetCurrentLevelType();

private:
	void CheckCurrentLevelType();

private:
	UPROPERTY()
	TObjectPtr<UMultiPlayPrjGameInstance> MultiGameInstance = nullptr;
	
	UPROPERTY()
	EMPSceneType CurrentLevelType = EMPSceneType::Title;

	const FName TitleLevelName = "MultiPlayPrjEntry";
	const FName InGameLevelName = "MultiPlayPrjInGame";
};
