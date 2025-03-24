// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPWidgetBase.generated.h"

class UUISubsystem;
class UButton;

UCLASS()
class MULTIPLAYPRJ_API UMPWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UUISubsystem* NewUISubsystem);
	virtual TSharedPtr<SWidget> GetTargetWidget();

protected:
	UFUNCTION()
	void OnClickedMoveTitle();

	UFUNCTION()
	void OnClickedQuitGame();

	UFUNCTION()
	void OnClickedMoveInGame();
	
protected:
	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem = nullptr;

	TObjectPtr<UButton> MoveTitleButton;
	TObjectPtr<UButton> QuitGameButton;
	TObjectPtr<UButton> MoveInGameButton;
};
