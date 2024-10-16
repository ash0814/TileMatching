// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGrid.h"
#include "Tile.h"
#include "PuzzleGameModeBase.h"
#include "PuzzleGameInstance.h"
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
	while (IsTileMatcing())
	{
		MoveTileDown();
	}
}

void ATileGrid::CheckSelection()
{
	if (SelectedTiles.Num() >= 2) {
		int32 X1, Y1, X2, Y2;
		SelectedTiles[0]->GetTileIndex(X1, Y1);
		SelectedTiles[1]->GetTileIndex(X2, Y2);
		if (FMath::Abs(X1 - X2) + FMath::Abs(Y1 - Y2) == 1)
		{
			SwapTiles(SelectedTiles[0], SelectedTiles[1]);
			if (!IsTileMatcing())
			{
				SwapTiles(SelectedTiles[0], SelectedTiles[1]);
			}
			else {
				while (IsTileMatcing()) {
					DestroyTiles();
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

bool ATileGrid::IsTileMatcing()
{
	if (TilesToDestroy.Num() > 0) {
		TilesToDestroy.Empty();
	}
	for (int32 i = 0; i < SideLength; i++) {
		for (int32 j = 0; j < SideLength; j++) {
			if (TileGrid[i * SideLength + j]->GetTileType() == ETileType::TT_None) {
				continue;
			}
			// check same type tiles in row
			TArray<ATile*> RowSameTypeTiles;
			RowSameTypeTiles.Add(TileGrid[i * SideLength + j]);
			for (int32 k = j + 1; k < SideLength; k++) {
				if (TileGrid[i * SideLength + j]->GetTileType() == TileGrid[i * SideLength + k]->GetTileType()) {
					RowSameTypeTiles.Add(TileGrid[i * SideLength + k]);
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
			ColumnSameTypeTiles.Add(TileGrid[i * SideLength + j]);
			for (int32 k = i + 1; k < SideLength; k++) {
				if (TileGrid[i * SideLength + j]->GetTileType() == TileGrid[k * SideLength + j]->GetTileType()) {
					ColumnSameTypeTiles.Add(TileGrid[k * SideLength + j]);
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

	if (TilesToDestroy.Num() > 0) {
		return true;
	}
	return false;
}

void ATileGrid::DestroyTiles()
{
	//auto _GameInstance = Cast<UPuzzleGameInstance>(GetGameInstance());
	if (TilesToDestroy.Num() <= 3) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Score: 10"));
		OnTileMatched.Broadcast(10);
		//_GameInstance->AddScore(10);
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Score: 20"));
		//_GameInstance->AddScore(20);
		OnTileMatched.Broadcast(20);
	}
	// Delete the tiles
	for (ATile* Tile : TilesToDestroy) {
		Tile->SetTileType(ETileType::TT_None);
	}
	TilesToDestroy.Empty();
}

void ATileGrid::MoveTileDown()
{
	// if there are empty tiles, move the tiles above down
	for (int32 i = SideLength - 1; i >= 0; i--) {
		for (int32 j = 0; j < SideLength; j++) {
			// get closest non-empty tile
			if (TileGrid[i * SideLength + j]->GetTileType() == ETileType::TT_None) {
				for (int32 k = i - 1; k >= 0; k--) {
					if (TileGrid[k * SideLength + j]->GetTileType() != ETileType::TT_None) {
						TileGrid[i * SideLength + j]->SetTileType(TileGrid[k * SideLength + j]->GetTileType());
						TileGrid[k * SideLength + j]->SetTileType(ETileType::TT_None);
						break;
					}
				}
			}
		}
	}
	FillEmptyTiles();
}

void ATileGrid::FillEmptyTiles()
{
	for (ATile* Tile : TileGrid)
	{
		if (Tile->GetTileType() == ETileType::TT_None)
		{
			Tile->SetTileType(static_cast<ETileType>(FMath::RandRange(0, 5)));
		}
	}
}

void ATileGrid::SwapTiles(ATile* TileA, ATile* TileB)
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

