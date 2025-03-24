// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UISettings.generated.h"

class UMPWidgetBase;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "UISubsystemSettings"))
class MULTIPLAYPRJ_API UUISettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Config, Category = "WidgetClass")
	TSubclassOf<UMPWidgetBase> TitleWidgetClass = nullptr;
	
	UPROPERTY(EditAnywhere, Config, Category = "WidgetClass")
	TSubclassOf<UMPWidgetBase> InGameWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, Config, Category = "WidgetClass")
	TSubclassOf<UMPWidgetBase> ChatWidgetClass = nullptr;
};
