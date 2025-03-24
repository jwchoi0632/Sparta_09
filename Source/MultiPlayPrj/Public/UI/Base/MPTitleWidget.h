// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MPWidgetBase.h"
#include "MPTitleWidget.generated.h"

class UUISubsystem;
class UButton;

UCLASS()
class MULTIPLAYPRJ_API UMPTitleWidget : public UMPWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UUISubsystem* NewUISubsystem) override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;
};
