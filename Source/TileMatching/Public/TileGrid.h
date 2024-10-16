// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileMatched, int32, Score);

UCLASS()
class TILEMATCHING_API ATileGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<class ATile*> SelectedTiles;
	float TileSpacing;

	TArray<class ATile*> TileGrid;

	TArray<class ATile*> TilesToDestroy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Tile Grid")
	FOnTileMatched OnTileMatched;

	// Number of tiles in the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 SideLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	TSubclassOf<class ATile> TileClass;

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void GenerateGrid();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void CheckSelection();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	bool IsTileMatcing();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void DestroyTiles();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void MoveTileDown();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void FillEmptyTiles();

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void SwapTiles(ATile* TileA, ATile* TileB);

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void AddSelectedTile(ATile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void RemoveSelectedTile(ATile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void ClearSelectedTiles();
};
