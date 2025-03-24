// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameRuleComponent.h"

UGameRuleComponent::UGameRuleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UGameRuleComponent::SetQuestion()
{
	AnswerNums.Empty();

	for (int32 i = 0; i < 3; i++)
	{
		int32 Element = SelectAnswerNumber();
		AnswerNums.Add(Element);
	}
}

void UGameRuleComponent::CompareAnswer(const TArray<int32>& PlayerAnswer, int32& Strike, int32& Ball, FText& Result)
{
	Strike = 0;
	Ball = 0;

	for (int32 i = 0; i < PlayerAnswer.Num(); i++)
	{
		if (AnswerNums.Contains(PlayerAnswer[i]))
		{
			++Ball;
		}

		if (AnswerNums[i] == PlayerAnswer[i])
		{
			++Strike;
			--Ball;
		}
	}

	if (PlayerAnswer.Num() < AnswerNums.Num())
	{
		Result = FText::FromString(FString::Printf(TEXT("Out")));
		return;
	}

	if (Strike == 3)
	{
		Result = FText::FromString(FString::Printf(TEXT("Clear")));
		return;
	}

	if (Strike == 0 && Ball == 0)
	{
		Result = FText::FromString(FString::Printf(TEXT("Out")));
		return;
	}

	Result = FText::FromString(FString::Printf(TEXT("Foul")));
}

void UGameRuleComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

int32 UGameRuleComponent::SelectAnswerNumber()
{
	int32 Element = FMath::RandRange(1, 9);

	if (AnswerNums.Contains(Element))
	{
		Element = SelectAnswerNumber();
	}

	return Element;
}


