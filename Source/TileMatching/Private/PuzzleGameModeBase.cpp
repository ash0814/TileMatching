// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameModeBase.h"
#include "PuzzlePlayerController.h"
#include "Tile.h"
#include "TileGrid.h"
#include "PlayerWidget.h"
#include "PuzzleGameInstance.h"

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
			auto _GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
			if (_GameInstance) {
				_GameInstance->RegisterScoreObserver(PlayerWidget);
				_GameInstance->RegisterMoveObserver(PlayerWidget);
				_GameInstance->RegisterMyGameOverObserver(PlayerWidget);
			}
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
	auto _GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
	if (!CurrentTileGrid->IsAnyTileCanMove())
	{
		_GameInstance->SetGameOverMessage(FText::FromString("Any Tile Cannot Move : Game Over"));
		_GameInstance->NotifyMyGameOverObservers();
	}
}

