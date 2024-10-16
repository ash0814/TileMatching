// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

public:
	//UPROPERTY(BlueprintAssignable, Category = "Game State")
	//FOnScoreUpdated OnScoreChange;

	//UPROPERTY(BlueprintAssignable, Category = "Game State")
	//FOnMovesUpdated OnMovesChange;

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
};
