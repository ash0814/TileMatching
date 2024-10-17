// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameModeBase.h"
#include "PuzzlePlayerController.h"
#include "Tile.h"
#include "TileGrid.h"
#include "PlayerWidget.h"

APuzzleGameModeBase::APuzzleGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}

void APuzzleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    if (PlayerWidgetClass) {
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget) {
			PlayerWidget->AddToViewport();
		}
	}
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
    if (Tile->GetIsSelected()) {
        CurrentTileGrid->RemoveSelectedTile(Tile);
    }
    else {
        CurrentTileGrid->AddSelectedTile(Tile);
    }
    CurrentTileGrid->CheckSelection();
}
