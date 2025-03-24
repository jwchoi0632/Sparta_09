// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MPPlayerController.h"
#include "System/MultiPlayPrjGameInstance.h"
#include "System/MPGameState.h"
#include "System/MPGameMode.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "InputMappingContext.h"
#include "InputAction.h"


void AMPPlayerController::InitClient(const int32 Number)
{
	ResponseClientNumber(Number);
}

void AMPPlayerController::InitUserList()
{
	ResponseInitUserList();
}

void AMPPlayerController::SendMessage(const FName& UserName, const FText& Message)
{
	RequestSendChatMessage(UserName, Message);
}

void AMPPlayerController::NotifyStartGame()
{
	ResponseStartGame();
}

void AMPPlayerController::SendAnswer(const FName& UserName, const TArray<int32>& PlayerAnswer)
{
	SetInputMode(FInputModeGameOnly());
	RequestAnswerCompare(UserName, PlayerAnswer);
}

void AMPPlayerController::OnChangedTurn(const FTurnResultStruct& TurnResult)
{
	ResponseOnChangedTurn(TurnResult);
}

void AMPPlayerController::SendNotify(const FText& Notify, bool bNeedName, bool bIsWin)
{
	ResponseNotify(Notify, bNeedName, bIsWin);
}

void AMPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (IsValid(LocalPlayer))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (IsValid(Subsystem))
		{
			if (IsValid(IMC_Chat))
			{
				Subsystem->AddMappingContext(IMC_Chat, 0);
			}
		}
	}
}

void AMPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}

	if (!IsValid(IA_Chat))
	{
		return;
	}

	EnhancedInputComponent->BindAction(IA_Chat, ETriggerEvent::Triggered, this, &ThisClass::OnPressedEnterKey);
}

void AMPPlayerController::OnPressedEnterKey()
{
	if (!IsValid(MPGameInstance))
	{
		return;
	}

	TSharedPtr<SWidget> InputBox = MPGameInstance->GetChatInputBox();

	if (InputBox == nullptr)
	{
		return;
	}

	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(InputBox);
	SetInputMode(UIInputMode);
}

void AMPPlayerController::NotifyBeginPlay_Implementation()
{
	CheckValidOfGameMode();
	checkf(IsValid(MPGameMode), TEXT("GameMode is invalid"));
	MPGameMode->ResponseClientBegin();
}

void AMPPlayerController::ResponseInitUserList_Implementation()
{
	CheckValidOfGameInstance();
	checkf(IsValid(MPGameInstance), TEXT("GameInstance is invalid"));
	RequestAddUserList(MPGameInstance->GetUserName());
}

void AMPPlayerController::RequestAddUserList_Implementation(const FName& UserName)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->AddUserList(UserName);
}

void AMPPlayerController::RequestSendChatMessage_Implementation(const FName& UserName, const FText& Message)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->SendChatMessage(UserName, Message);
}

void AMPPlayerController::RequestLoginNotify_Implementation(const FName& UserName)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->InitLocalState(UserName);
}

void AMPPlayerController::ResponseClientNumber_Implementation(const int32 Number)
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	ClientName = (FName)FString::Printf(TEXT("User%d"), Number);
	CheckValidOfGameInstance();
	checkf(IsValid(MPGameInstance), TEXT("GameInstance is invalid"));

	MPGameInstance->SetUserName(ClientName);
	MPGameInstance->SetPlayerController(this);
	MPGameInstance->AddUIOfCurrentLevel();

	GetWorld()->GetTimerManager().SetTimer(Timer, FTimerDelegate::CreateLambda([&]()
		{
			RequestLoginNotify(ClientName);
			NotifyBeginPlay();
		}), 0.2f, false);
}

void AMPPlayerController::RequestAnswerCompare_Implementation(const FName& UserName, const TArray<int32>& PlayerAnswer)
{
	CheckValidOfGameMode();
	checkf(IsValid(MPGameMode), TEXT("GameMode is invalid"));
	MPGameMode->ResponseClientAnswer(UserName, PlayerAnswer);
}

void AMPPlayerController::ResponseOnChangedTurn_Implementation(const FTurnResultStruct& TurnResult)
{
	RequestApplyChangedTurn(TurnResult, ClientName);
}

void AMPPlayerController::RequestApplyChangedTurn_Implementation(const FTurnResultStruct& TurnResult, const FName& UserName)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->NotifyChangedTurn(TurnResult, UserName);
}

void AMPPlayerController::ResponseNotify_Implementation(const FText& Notify, bool bNeedName, bool bIsWin)
{
	FText NotifyMessage = Notify;

	if (bNeedName)
	{
		NotifyMessage = FText::FromString(FString::Printf(TEXT("%s %s"), *ClientName.ToString(), *Notify.ToString()));
	}

	RequestAddNotify(NotifyMessage, bIsWin, ClientName);
}

void AMPPlayerController::RequestAddNotify_Implementation(const FText& Notify, bool bIsWin, const FName& UserName)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->SendNotifyMessage(Notify, bIsWin, UserName);
}

void AMPPlayerController::CheckValidOfGameInstance()
{
	if (!IsValid(MPGameInstance))
	{
		MPGameInstance = GetGameInstance<UMultiPlayPrjGameInstance>();
	}
}

void AMPPlayerController::CheckValidOfGameState()
{
	if (!IsValid(MPGameState))
	{
		MPGameState = GetWorld()->GetGameState<AMPGameState>();
	}
}

void AMPPlayerController::CheckValidOfGameMode()
{
	if (!IsValid(MPGameMode))
	{
		MPGameMode = GetWorld()->GetAuthGameMode<AMPGameMode>();
	}
}

void AMPPlayerController::ResponseStartGame_Implementation()
{
	RequestApplyStartGame(ClientName);
}

void AMPPlayerController::RequestApplyStartGame_Implementation(const FName& UserName)
{
	CheckValidOfGameState();
	checkf(IsValid(MPGameState), TEXT("GameState is invalid"));
	MPGameState->NotifyGameStart(UserName);
}
