// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGrid.h"
#include "Tile.h"

// Sets default values
ATileGrid::ATileGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SideLength = 6;
	TileSpacing = 105.0f;
	//GenerateGrid();
}

// Called when the game starts or when spawned
void ATileGrid::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateGrid();
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
				NewTile->SetTileType(static_cast<ETileType>(FMath::RandRange(0, 3)));
				TileGrid.Add(NewTile);
			}
		}
	}
}

