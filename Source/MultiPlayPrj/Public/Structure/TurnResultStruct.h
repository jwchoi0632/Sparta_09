// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnResultStruct.generated.h"


USTRUCT(BlueprintType)
struct MULTIPLAYPRJ_API FTurnResultStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FName UserName = "";

	UPROPERTY()
	FText Result = FText::GetEmpty();

	UPROPERTY()
	int32 Strike = 0;

	UPROPERTY()
	int32 Ball = 0;

	UPROPERTY()
	TArray<int32> InputNums;
};
