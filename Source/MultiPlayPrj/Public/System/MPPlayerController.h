// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPPlayerController.generated.h"

class UMultiPlayPrjGameInstance;
class AMPGameState;
class AMPGameMode;
class UInputMappingContext;
class UInputAction;
struct FTurnResultStruct;

UCLASS()
class MULTIPLAYPRJ_API AMPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void InitClient(const int32 Number);
	void InitUserList();
	void SendMessage(const FName& UserName, const FText& Message);
	void NotifyStartGame();
	void SendAnswer(const FName& UserName, const TArray<int32>& PlayerAnswer);
	void OnChangedTurn(const FTurnResultStruct& TurnResult);
	void SendNotify(const FText& Notify, bool bNeedName, bool bIsWin);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OnPressedEnterKey();

	UFUNCTION(Client, Reliable)
	void ResponseClientNumber(const int32 Number);

	UFUNCTION(Server, Reliable)
	void NotifyBeginPlay();

	UFUNCTION(Client, Reliable)
	void ResponseInitUserList();

	UFUNCTION(Server, Reliable)
	void RequestAddUserList(const FName& UserName);

	UFUNCTION(Server, Unreliable)
	void RequestLoginNotify(const FName& UserName);

	UFUNCTION(Server, Unreliable)
	void RequestSendChatMessage(const FName& UserName, const FText& Message);

	UFUNCTION(Client, Reliable)
	void ResponseStartGame();

	UFUNCTION(Server, Reliable)
	void RequestApplyStartGame(const FName& UserName);

	UFUNCTION(Server, Reliable)
	void RequestAnswerCompare(const FName& UserName, const TArray<int32>& PlayerAnswer);

	UFUNCTION(Client, Reliable)
	void ResponseOnChangedTurn(const FTurnResultStruct& TurnResult);

	UFUNCTION(Server, Reliable)
	void RequestApplyChangedTurn(const FTurnResultStruct& TurnResult, const FName& UserName);

	UFUNCTION(Client, Reliable)
	void ResponseNotify(const FText& Notify, bool bNeedName, bool bIsWin);

	UFUNCTION(Server, Reliable)
	void RequestAddNotify(const FText& Notify, bool bIsWin, const FName& UserName);

	void CheckValidOfGameInstance();
	void CheckValidOfGameState();
	void CheckValidOfGameMode();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Chat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> IA_Chat;

protected:
	UPROPERTY()
	TObjectPtr<UMultiPlayPrjGameInstance> MPGameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<AMPGameState> MPGameState = nullptr;

	UPROPERTY()
	TObjectPtr<AMPGameMode> MPGameMode = nullptr;

	FName ClientName = "";

	FTimerHandle Timer;
};
