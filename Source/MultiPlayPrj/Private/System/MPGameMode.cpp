// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MPGameMode.h"
#include "System/MPPlayerController.h"
#include "System/MPGameState.h"
#include "Kismet/GameplayStatics.h"
#include "System/GameRuleComponent.h"
#include "Structure/TurnResultStruct.h"

AMPGameMode::AMPGameMode()
{
	GameRule = CreateDefaultSubobject<UGameRuleComponent>(TEXT("GameRule"));
}

void AMPGameMode::InitMPGameMode()
{
	bUseSeamlessTravel = true;
	ReadyCount = 0;
	WaveCount = 0;
	ClientIndex = 0;
	ActiveCount = 0;
	TimeValue = 10;
	Clients.Empty();
	ActiveClients.Empty();
}

void AMPGameMode::StartGame()
{
	++WaveCount;
	InitActiveClients();
	GameRule->SetQuestion();

	AMPPlayerController* NewPC = Cast<AMPPlayerController>(Clients[ClientIndex]);
	NewPC->NotifyStartGame();

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::CheckTime, 1.0f, true);
}

void AMPGameMode::EndGame()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);

	Cast<AMPGameState>(GameState)->QuitAllClients();

	InitMPGameMode();
}

void AMPGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	Super::EndPlay(EndPlayReason);
}

void AMPGameMode::ResponseClientBegin()
{
	++ReadyCount;

	if (ReadyCount >= 2 && ReadyCount == Clients.Num())
	{
		for (APlayerController* Client : Clients)
		{
			AMPPlayerController* NewPC = Cast<AMPPlayerController>(Client);

			if (IsValid(NewPC))
			{
				NewPC->InitUserList();
			}
		}

		StartGame();
	}
}

void AMPGameMode::ResponseClientAnswer(const FName& UserName, const TArray<int32>& PlayerAnswer)
{
	GameRule->CompareAnswer(PlayerAnswer, Strike, Ball, ResultText);

	FTurnResultStruct Result;

	Result.UserName = UserName;
	Result.InputNums = PlayerAnswer;
	Result.Strike = Strike;
	Result.Ball = Ball;
	Result.Result = ResultText;

	CheckClear(Result);
}

void AMPGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitMPGameMode();
}

void AMPGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

	AMPPlayerController* NewPC = Cast<AMPPlayerController>(PlayerController);

	if (IsValid(NewPC))
	{
		Clients.Add(NewPC);
		ActiveClients.Add(NewPC, true);
		NewPC->InitClient(NumPlayers);
	}
}

void AMPGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	EndGame();
}

void AMPGameMode::PostSeamlessTravel()
{

}

void AMPGameMode::CheckTime()
{
	--TimeValue;

	if (TimeValue < 0)
	{
		TimeValue = 10;
	}

	Cast<AMPGameState>(GameState)->NotifyChangedTime(TimeValue);
}

void AMPGameMode::CheckClear(const FTurnResultStruct& TurnResult)
{
	if (TurnResult.Result.ToString().Contains("Out"))
	{
		--ActiveCount;
		ActiveClients[Clients[ClientIndex]] = false;
	}

	ChangeTargetClient(TurnResult);

	if (TurnResult.Result.ToString().Contains("Clear"))
	{
		StartGame();
	}

	if (WaveCount > 5)
	{
		EndGame();
	}
}

void AMPGameMode::ChangeTargetClient(const FTurnResultStruct& TurnResult)
{
	++ClientIndex;
	ClientIndex = ClientIndex % Clients.Num();

	if (ActiveClients[Clients[ClientIndex]] == false)
	{
		ChangeTargetClient(TurnResult);
		return;
	}

	TimeValue = 10;

	AMPPlayerController* NewPC = Cast<AMPPlayerController>(Clients[ClientIndex]);
	NewPC->OnChangedTurn(TurnResult);

	if (ActiveCount == 1)
	{
		FText Notify = FText::FromString(FString::Printf(TEXT("Win!")));
		NewPC->SendNotify(Notify, true, true);
		StartGame();
	}
}

void AMPGameMode::InitActiveClients()
{
	ActiveCount = Clients.Num();

	for (TPair<TObjectPtr<APlayerController>, bool>& pair : ActiveClients)
	{
		pair.Value = true;
	}
}
