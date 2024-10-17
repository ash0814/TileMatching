// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Observer.h"
#include "PuzzleGameInstance.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, int32, PlayerScore);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovesUpdated, int32, RemainingMoves);
/**
 * 
 */
UCLASS()
class TILEMATCHING_API UPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPuzzleGameInstance();

	TArray<TScriptInterface<class IObserver>> ScoreObservers;
	TArray<TScriptInterface<class IObserver>> MoveObservers;
	TArray<TScriptInterface<class IObserver>> MyGameOverObservers;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	int32 PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	int32 RemainingMoves;

	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void AddScore(int32 Score);

	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void DecreaseMoves();

	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void ResetGameState();

	void RegisterScoreObserver(TScriptInterface<class IObserver> Observer);
	void UnregisterScoreObserver(TScriptInterface<class IObserver> Observer);
	void NotifyScoreObservers();

	void RegisterMoveObserver(TScriptInterface<class IObserver> Observer);
	void UnregisterMoveObserver(TScriptInterface<class IObserver> Observer);
	void NotifyMoveObservers();

	void RegisterMyGameOverObserver(TScriptInterface<class IObserver> Observer);
	void UnregisterMyGameOverObserver(TScriptInterface<class IObserver> Observer);
	void NotifyMyGameOverObservers();
	FText GameOverMessage;

	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void SetGameOverMessage(FText Message);
};
