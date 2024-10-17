// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"

UPuzzleGameInstance::UPuzzleGameInstance()
{
	PlayerScore = 0;
	RemainingMoves = 30;
}

void UPuzzleGameInstance::AddScore(int32 Score)
{
	PlayerScore += Score;
	NotifyScoreObservers();
}

void UPuzzleGameInstance::DecreaseMoves()
{
	if (RemainingMoves > 0)
		RemainingMoves--;
	NotifyMoveObservers();
	if (RemainingMoves == 0)
	{
		SetGameOverMessage(FText::FromString("No More Moves : Game Over"));
		NotifyMyGameOverObservers();
	}
}

void UPuzzleGameInstance::ResetGameState()
{
	PlayerScore = 0;
	RemainingMoves = 30;
}

void UPuzzleGameInstance::RegisterScoreObserver(TScriptInterface<class IObserver> Observer)
{
	ScoreObservers.Add(Observer);
}

void UPuzzleGameInstance::UnregisterScoreObserver(TScriptInterface<class IObserver> Observer)
{
	ScoreObservers.Remove(Observer);
}

void UPuzzleGameInstance::NotifyScoreObservers()
{
	for (TScriptInterface<IObserver> Observer : ScoreObservers)
	{
		if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			IObserver::Execute_OnNotifyScore(Observer.GetObject(), PlayerScore);
		}
	}
}

void UPuzzleGameInstance::RegisterMoveObserver(TScriptInterface<class IObserver> Observer)
{
	MoveObservers.Add(Observer);
}

void UPuzzleGameInstance::UnregisterMoveObserver(TScriptInterface<class IObserver> Observer)
{
	MoveObservers.Remove(Observer);
}

void UPuzzleGameInstance::NotifyMoveObservers()
{
	for (TScriptInterface<IObserver> Observer : MoveObservers)
	{
		if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			IObserver::Execute_OnNotifyMoves(Observer.GetObject(), RemainingMoves);
		}
	}
}


void UPuzzleGameInstance::RegisterMyGameOverObserver(TScriptInterface<class IObserver> Observer)
{
	MyGameOverObservers.Add(Observer);
}

void UPuzzleGameInstance::UnregisterMyGameOverObserver(TScriptInterface<class IObserver> Observer)
{
	MyGameOverObservers.Remove(Observer);
}
void UPuzzleGameInstance::NotifyMyGameOverObservers()
{
	for (TScriptInterface<IObserver> Observer : MyGameOverObservers)
	{
		if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			IObserver::Execute_OnNotifyMyGameOver(Observer.GetObject(), GameOverMessage);
		}
	}
}


void UPuzzleGameInstance::SetGameOverMessage(FText Message)
{
	GameOverMessage = Message;
}
