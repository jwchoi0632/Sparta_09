// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRuleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYPRJ_API UGameRuleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGameRuleComponent();

	void SetQuestion();
	void CompareAnswer(const TArray<int32>& PlayerAnswer, int32& Strike, int32& Ball, FText& Result);

protected:
	virtual void BeginPlay() override;

private:
	int32 SelectAnswerNumber();

private:
	TArray<int32> AnswerNums;
};
