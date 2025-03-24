// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MPGameState.generated.h"

class AMPPlayerController;
class UMultiPlayPrjGameInstance;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API AMPGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	void InitLocalState(const FName& UserName);
	void SendChatMessage(const FName& UserName, const FText& Message);
	void AddUserList(const FName& UserName);
	void NotifyGameStart(const FName& UserName);
	void NotifyChangedTurn(const FTurnResultStruct& TurnResult, const FName& TargetName);
	void NotifyChangedTime(const int32 TimeValue);
	void SendNotifyMessage(const FText& Notify, bool bIsWin, const FName& UserName);
	void QuitAllClients();
	/*void SetTime(const int32 TimeValue);*/

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(NetMulticast, Unreliable)
	void ResponseClientLogin(const FName& UserName);

	UFUNCTION(NetMulticast, Unreliable)
	void ResponseMessageLog(const FName& UserName, const FText& Message);

	UFUNCTION(NetMulticast, Unreliable)
	void ResponseGameStarted(const FName& UserName);

	UFUNCTION(NetMulticast, Reliable)
	void ResponseUserList(const FName& UserName);

	UFUNCTION(NetMulticast, Reliable)
	void ResponseEndTurn(const FTurnResultStruct& TurnResult, const FName& TargetName);

	UFUNCTION(NetMulticast, Reliable)
	void ResponseOnChangedTime(const int32 TimeValue);

	UFUNCTION(NetMulticast, Reliable)
	void ResponseNotifyMessage(const FText& Notify, bool bIsWin, const FName& UserName);

	UFUNCTION(NetMulticast, Reliable)
	void ResponseQuit();

	/*UFUNCTION()
	void OnRep_Timer();*/

private:
	UPROPERTY()
	TObjectPtr<UMultiPlayPrjGameInstance> MPGameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<AMPPlayerController> MPPlayerController = nullptr;

	/*UPROPERTY(ReplicatedUsing = OnRep_Timer);
	int32 Time = 0;*/
};
