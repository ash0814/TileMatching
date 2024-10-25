// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGrid.h"
#include "Tile.h"
#include "PuzzleGameModeBase.h"
#include "PuzzleGameInstance.h"
#include "TileCommandInvoker.h"
#include "SwapTileCommand.h"
#include <queue>
#include <vector>
#include <algorithm>

// Sets default values
ATileGrid::ATileGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SideLength = 6;
	TileSpacing = 105.0f;
}

// Called when the game starts or when spawned
void ATileGrid::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateGrid();

	
	auto _GameMode = Cast<APuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
	if (_GameMode)
	{
		_GameMode->SetCurrentTileGrid(this);
	}
}

// Called every frame
void ATileGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATileGrid::GenerateGrid()
{
	// Clear the grid
	TileGrid.Empty();

	// Calculate the center of the grid
	FVector GridCenter = GetActorLocation();
	GridCenter.X -= (SideLength * TileSpacing) / 2;
	GridCenter.Y -= (SideLength * TileSpacing) / 2;

	// Generate the grid
	for (int32 i = 0; i < SideLength; i++)
	{
		for (int32 j = 0; j < SideLength; j++)
		{
			FVector TileLocation = GridCenter;
			TileLocation.X += i * TileSpacing;
			TileLocation.Y += j * TileSpacing;

			if (TileClass) {
				ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, TileLocation, FRotator::ZeroRotator);
				NewTile->SetTileType(static_cast<ETileType>(FMath::RandRange(0, 5)));
				NewTile->SetTileIndex(i, j);
				NewTile->SetTileGrid(this);
				TileGrid.Add(NewTile);
			}
		}
	}
	
	// Tile Generation with Async Task
	/*
	for (int32 i = 0; i < SideLength; i++) {
		for (int32 j = 0; j < SideLength; j++) {
			AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, i, j]() {
				ETileType NewTileType = static_cast<ETileType>(FMath::RandRange(0, 5));

				AsyncTask(ENamedThreads::GameThread, [this, i, j, NewTileType]() {
					FVector GridCenter = GetActorLocation();
					GridCenter.X -= (SideLength * TileSpacing) / 2;
					GridCenter.Y -= (SideLength * TileSpacing) / 2;

					FVector TileLocation = GridCenter;
					TileLocation.X += i * TileSpacing;
					TileLocation.Y += j * TileSpacing;

					if (TileClass) {
						ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, TileLocation, FRotator::ZeroRotator);
						NewTile->SetTileType(NewTileType);
						NewTile->SetTileIndex(i, j);
						NewTile->SetTileGrid(this);
						TileGrid.Add(NewTile);
					}
				});
			});
		}
	}
	*/
	while (IsTileMatching())
	{
		MoveTileDown();
	}
}

ATile* ATileGrid::GetTileByIndex(int32 IndexX, int32 IndexY)
{
	if (IndexX >= 0 && IndexX < SideLength && IndexY >= 0 && IndexY < SideLength)
	{
		for (auto T : TileGrid) {
			int32 X, Y;
			T->GetTileIndex(X, Y);
			if (X == IndexX && Y == IndexY)
				return T;
		}
	}
	return nullptr;
}

bool ATileGrid::IsSelectedTilesNeighbour()
{
	if (SelectedTiles.Num() < 2) {
		return false;
	}
	int32 X1, Y1, X2, Y2;
	SelectedTiles[0]->GetTileIndex(X1, Y1);
	SelectedTiles[1]->GetTileIndex(X2, Y2);
	if (FMath::Abs(X1 - X2) + FMath::Abs(Y1 - Y2) == 1) {
		return true;
	}
	return false;
}

void ATileGrid::CheckSelection()
{
	if (SelectedTiles.Num() >= 2) {
		if (IsSelectedTilesNeighbour())
		{
			auto _GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
			_GameInstance->DecreaseMoves();

			USwapTileCommand * SwapTileCommand = NewObject<USwapTileCommand>();
			SwapTileCommand->Initialize(SelectedTiles[0], SelectedTiles[1]);

			ATileCommandInvoker * CommandInvoker = GetWorld()->SpawnActor<ATileCommandInvoker>();
			CommandInvoker->ExecuteCommand(SwapTileCommand);

			// SwapTileMove(SelectedTiles[0], SelectedTiles[1]);
			if (!IsTileMatching(SelectedTiles[0]) && !IsTileMatching(SelectedTiles[1])) {
				// SwapTileMove(SelectedTiles[0], SelectedTiles[1]);
				CommandInvoker->UndoCommand();
			}
			else {
				while (IsTileMatching()) {
					MoveTileDown();
				}
			}
			ClearSelectedTiles();
		}
		else {
			RemoveSelectedTile(SelectedTiles[0]);
		}
	}
}

bool ATileGrid::IsTileMatching()
{
	TArray<ATile*> TilesToDestroy;
	for (int32 i = 0; i < SideLength; i++) {
		for (int32 j = 0; j < SideLength; j++) {
			if (!GetTileByIndex(i, j) || GetTileByIndex(i, j)->GetTileType() == ETileType::TT_None) {
				continue;
			}
			// check same type tiles in row
			TArray<ATile*> RowSameTypeTiles;
			RowSameTypeTiles.Add(GetTileByIndex(i, j));
			for (int32 k = j + 1; k < SideLength; k++) {
				if (GetTileByIndex(i, k) && GetTileByIndex(i, j)->GetTileType() == GetTileByIndex(i, k)->GetTileType()) {
					RowSameTypeTiles.Add(GetTileByIndex(i, k));
				}
				else {
					break;
				}
			}
			if (RowSameTypeTiles.Num() >= 3) {
				for (ATile* Tile : RowSameTypeTiles) {
					TilesToDestroy.Add(Tile);
				}
			}
			// check same type tiles in column
			TArray<ATile*> ColumnSameTypeTiles;
			ColumnSameTypeTiles.Add(GetTileByIndex(i, j));
			for (int32 k = i + 1; k < SideLength; k++) {
				if (GetTileByIndex(k, j) && GetTileByIndex(i, j)->GetTileType() == GetTileByIndex(k, j)->GetTileType()) {
					ColumnSameTypeTiles.Add(GetTileByIndex(k, j));
				}
				else {
					break;
				}
			}
			if (ColumnSameTypeTiles.Num() >= 3) {
				for (ATile* Tile : ColumnSameTypeTiles) {
					TilesToDestroy.Add(Tile);
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("TilesToDestroy.Num() : %d"), TilesToDestroy.Num());
	if (TilesToDestroy.Num() > 0) {
		DestroyTiles(TilesToDestroy);
		return true;
	}
	return false;
}

bool ATileGrid::IsTileMatching(ATile* Tile)
{
	int32 X, Y;
	Tile->GetTileIndex(X, Y);
	ETileType TileType = Tile->GetTileType();
	int32 Count = 1;
	for (int32 i = X + 1; i < SideLength; i++) {
		if (GetTileByIndex(i, Y) && GetTileByIndex(i, Y)->GetTileType() == TileType) Count++;
		else break;
	}
	for (int32 i = X - 1; i >= 0; i--) {
		if (GetTileByIndex(i, Y) && GetTileByIndex(i, Y)->GetTileType() == TileType) Count++;
		else break;
	}
	if (Count >= 3)
		return true;
	Count = 1;
	for (int32 j = Y + 1; j < SideLength; j++) {
		if (GetTileByIndex(X, j) && GetTileByIndex(X, j)->GetTileType() == TileType) Count++;
		else break;
	}
	for (int32 j = Y - 1; j >= 0; j--) {
		if (GetTileByIndex(X, j) && GetTileByIndex(X, j)->GetTileType() == TileType) Count++;
		else break;
	}
	if (Count >= 3)
		return true;
	return false;
}

void ATileGrid::DestroyTiles(TArray<class ATile*> TilesToDestroy)
{
	auto _GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
	if (TilesToDestroy.Num() <= 3) {
		_GameInstance->AddScore(10);
	} else {
		_GameInstance->AddScore(20);
	}
	for (ATile* Tile : TilesToDestroy) {
		Tile->Die();
	}
}

void ATileGrid::MoveTileDown()
{
	// if there are empty tiles, move the tiles above down
	for (int32 i = SideLength - 1; i >= 0; i--) {
		for (int32 j = 0; j < SideLength; j++) {
			// get closest non-empty tile
			if (!GetTileByIndex(i, j)) {
				for (int32 k = i - 1; k >= 0; k--) {
					if (GetTileByIndex(k, j)) {
						FVector GridCenter = GetActorLocation();
						GridCenter.X -= (SideLength * TileSpacing) / 2;
						GridCenter.Y -= (SideLength * TileSpacing) / 2;
						FVector TileLocation = GridCenter;
						TileLocation.X += i * TileSpacing;
						TileLocation.Y += j * TileSpacing;
						// move the tile down
						GetTileByIndex(k, j)->MoveTo(TileLocation, i, j);
						break;
					}
					else {
						continue;
					}
				}
			}
		}
	}
	FillEmptyTiles();
}

void ATileGrid::FillEmptyTiles()
{
	for (int32 i = 0; i < SideLength; i++)
	{
		for (int32 j = 0; j < SideLength; j++)
		{
			if (GetTileByIndex(i, j)) {
				continue;
			}
			else {
				FVector GridCenter = GetActorLocation();
				GridCenter.X -= (SideLength * TileSpacing) / 2;
				GridCenter.Y -= (SideLength * TileSpacing) / 2;
				FVector TileLocation = GridCenter;
				TileLocation.X += i * TileSpacing;
				TileLocation.Y += j * TileSpacing;
				if (TileClass) {
					ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, TileLocation, FRotator::ZeroRotator);
					NewTile->SetTileType(static_cast<ETileType>(FMath::RandRange(0, 5)));
					NewTile->SetTileIndex(i, j);
					NewTile->SetTileGrid(this);
					TileGrid.Add(NewTile);
				}
			}
		}
	}
}

void ATileGrid::SwapTileByType(ATile* TileA, ATile* TileB)
{
	ETileType TempType = TileA->GetTileType();
	TileA->SetTileType(TileB->GetTileType());
	TileB->SetTileType(TempType);
}

void ATileGrid::AddSelectedTile(ATile* Tile)
{
	Tile->SetSelected(true);
	SelectedTiles.Add(Tile);
}

void ATileGrid::RemoveSelectedTile(ATile* Tile)
{
	Tile->SetSelected(false);
	int32 findIdx = SelectedTiles.Find(Tile);
	if (findIdx != INDEX_NONE)
	{
		SelectedTiles.RemoveAt(findIdx);
	}
}

void ATileGrid::ClearSelectedTiles()
{
	for (ATile* Tile : SelectedTiles)
	{
		Tile->SetSelected(false);
	}
	SelectedTiles.Empty();
}

bool ATileGrid::IsAnyTileCanMove()
{
	for (int32 i = 0; i < SideLength; i++) {
		for (int32 j = 0; j < SideLength; j++) {
			ATile * Tile = GetTileByIndex(i, j);
			ATile * RightTile = nullptr;
			ATile * DownTile = nullptr;
			if (Tile) {
				if (i < SideLength - 1) {
					DownTile = GetTileByIndex(i + 1, j);
					if (DownTile) {
						SwapTileByType(Tile, DownTile);
						if (IsTileMatching(Tile) || IsTileMatching(DownTile)) {
							SwapTileByType(Tile, DownTile);
							return true;
						}
						SwapTileByType(Tile, DownTile);
					}
				}
				if (j < SideLength - 1) {
					RightTile = GetTileByIndex(i, j + 1);
					if (RightTile) {
						SwapTileByType(Tile, RightTile);
						if (IsTileMatching(Tile) || IsTileMatching(RightTile)) {
							SwapTileByType(Tile, RightTile);
							return true;
						}
						SwapTileByType(Tile, RightTile);
					}
				}
			}
		}
	}
	return false;
}

