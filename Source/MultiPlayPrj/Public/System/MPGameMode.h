// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MPGameMode.generated.h"

class UGameRuleComponent;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API AMPGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMPGameMode();
	virtual void InitMPGameMode();
	virtual void StartGame();
	virtual void EndGame();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ResponseClientBegin();
	void ResponseClientAnswer(const FName& UserName, const TArray<int32>& PlayerAnswer);

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* PlayerController) override;
	virtual void Logout(AController* Exiting) override;
	virtual void PostSeamlessTravel() override;

	void CheckTime();
	void CheckClear(const FTurnResultStruct& TurnResult);
	void ChangeTargetClient(const FTurnResultStruct& TurnResult);
	void InitActiveClients();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UGameRuleComponent> GameRule;

private:
	TArray<TObjectPtr<APlayerController>> Clients;
	TMap<TObjectPtr<APlayerController>, bool> ActiveClients;

	int32 ReadyCount = 0;
	int32 TimeValue = 10;
	int32 ClientIndex = 0;
	int32 WaveCount = 0;
	int32 ActiveCount = 0;

	int32 Ball = 0;
	int32 Strike = 0;
	FText ResultText = FText::GetEmpty();

	FTimerHandle Timer;
};
