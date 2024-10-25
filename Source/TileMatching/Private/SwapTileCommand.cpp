// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapTileCommand.h"
#include "Tile.h"

void USwapTileCommand::Initialize(ATile* InTileA, ATile* InTileB)
{
	TileA = InTileA;
	TileB = InTileB;
	TileAOriginalLocation = TileA->GetActorLocation();
	TileBOriginalLocation = TileB->GetActorLocation();
	TileA->GetTileIndex(TileAOriginalIndexX, TileAOriginalIndexY);
	TileB->GetTileIndex(TileBOriginalIndexX, TileBOriginalIndexY);
}

void USwapTileCommand::Execute()
{
	TileA->MoveTo(TileBOriginalLocation, TileBOriginalIndexX, TileBOriginalIndexY);
	TileB->MoveTo(TileAOriginalLocation, TileAOriginalIndexX, TileAOriginalIndexY);
}

void USwapTileCommand::Undo()
{
	TileA->MoveTo(TileAOriginalLocation, TileAOriginalIndexX, TileAOriginalIndexY);
	TileB->MoveTo(TileBOriginalLocation, TileBOriginalIndexX, TileBOriginalIndexY);
}
