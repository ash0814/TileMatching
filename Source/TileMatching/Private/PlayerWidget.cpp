// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PuzzleGameInstance.h"
#include "TileGrid.h"

void UPlayerWidget::OnNotifyScore_Implementation(int32 Score)
{
	UpdateScore(Score);
}

void UPlayerWidget::OnNotifyMoves_Implementation(int32 Moves)
{
	UpdateMoves(Moves);
}



void UPlayerWidget::OnNotifyMyGameOver_Implementation(const FText& msg)
{
	UpdateGameOver(msg);
}

void UPlayerWidget::UpdateScore(int32 NewScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::FromInt(NewScore)));
	}
}

void UPlayerWidget::UpdateMoves(int32 Moves)
{
	if (LeftMove)
	{
		LeftMove->SetText(FText::FromString(FString::FromInt(Moves)));
	}
}

void UPlayerWidget::UpdateGameOver(FText GameOverMessage)
{
	if (GameOverText)
	{
		GameOverText->SetVisibility(ESlateVisibility::Visible);
		GameOverText->SetText(GameOverMessage);

		GetOwningPlayer()->bShowMouseCursor = true;
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		if (UndoButton)
		{
			UndoButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

