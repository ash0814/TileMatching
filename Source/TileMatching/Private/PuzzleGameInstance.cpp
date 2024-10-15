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
}

void UPuzzleGameInstance::DecreaseMoves()
{
	if (RemainingMoves > 0)
	{
		RemainingMoves--;
	}
}

void UPuzzleGameInstance::ResetGameState()
{
	PlayerScore = 0;
	RemainingMoves = 30;
}
