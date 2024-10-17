// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PuzzleGameInstance.h"
#include "TileGrid.h"

void UPlayerWidget::BindToScore(ATileGrid* Grid)
{
}

void UPlayerWidget::UpdateScore(int32 NewScore)
{
	if (Score)
	{
		Score->SetText(FText::FromString(FString::FromInt(NewScore)));
	}
}

void UPlayerWidget::UpdateMoves(int32 Moves)
{
	if (LeftMove)
	{
		LeftMove->SetText(FText::FromString(FString::FromInt(Moves)));
	}
}
