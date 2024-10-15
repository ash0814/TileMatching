// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameModeBase.h"
#include "PuzzlePlayerController.h"
#include "Tile.h"
#include "TileGrid.h"

APuzzleGameModeBase::APuzzleGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}

void APuzzleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzleGameModeBase::SetCurrentTileGrid(ATileGrid* TileGrid)
{
	CurrentTileGrid = TileGrid;
}

ATileGrid* APuzzleGameModeBase::GetCurrentTileGrid()
{
    return CurrentTileGrid;
}


void APuzzleGameModeBase::OnClickTile(ATile* Tile)
{
    int32 X, Y;
    Tile->GetTileIndex(X, Y);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Tile Index: (%d, %d)"), X, Y));
    if (Tile->GetIsSelected()) {
        Tile->SetSelected(false);
    }
    else {
        Tile->SetSelected(true);
    }
    CurrentTileGrid->CheckSelection();
}
