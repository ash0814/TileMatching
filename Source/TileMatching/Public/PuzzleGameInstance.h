// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

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
