// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */

class ATileGrid;
UCLASS()
class TILEMATCHING_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// bind to canvas panel
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftMove;

	UPROPERTY(meta = (BindWidget))
	class UButton* UndoButton;

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void BindToScore(ATileGrid* Grid);

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void UpdateScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void UpdateMoves(int32 Moves);
};
