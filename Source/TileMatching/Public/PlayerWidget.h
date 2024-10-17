// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Observer.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */

class ATileGrid;
UCLASS()
class TILEMATCHING_API UPlayerWidget : public UUserWidget, public IObserver
{
	GENERATED_BODY()

public:
	// bind to canvas panel
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftMove;

	UPROPERTY(meta = (BindWidget))
	class UButton* UndoButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameOverText;

	virtual void OnNotifyScore_Implementation(int32 Score) override;
	virtual void OnNotifyMoves_Implementation(int32 Moves) override;
	virtual void OnNotifyMyGameOver_Implementation(const FText& msg) override;

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void UpdateScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void UpdateMoves(int32 Moves);

	UFUNCTION(BlueprintCallable, Category = "Widget Function")
	void UpdateGameOver(FText GameOverMessage);
};
