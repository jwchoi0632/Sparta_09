// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MPTypes.generated.h"

UENUM(BlueprintType)
enum class EMPSceneType : uint8
{
	Title = 0,
	Lobby,
	InGame,
	Lodding
};

UENUM(BlueprintType)
enum class EMPWidgetType : uint8
{
	TitleWidget = 0,
	InGameWidget,
	ChatWidget
};


UCLASS()
class MULTIPLAYPRJ_API UMPTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
