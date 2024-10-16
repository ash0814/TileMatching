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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Score: %d"), PlayerScore));
	//OnScoreChange.Broadcast(PlayerScore);
}

void UPuzzleGameInstance::DecreaseMoves()
{
	if (RemainingMoves > 0)
		RemainingMoves--;
	//OnMovesChange.Broadcast(RemainingMoves);
}

void UPuzzleGameInstance::ResetGameState()
{
	PlayerScore = 0;
	RemainingMoves = 30;
	//OnScoreChange.Broadcast(PlayerScore);
	//OnMovesChange.Broadcast(RemainingMoves);
}
