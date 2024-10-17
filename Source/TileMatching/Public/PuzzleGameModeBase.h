// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Observer.h"
#include "PuzzleGameModeBase.generated.h"

class ATile;

/**
 * 
 */
UCLASS()
class TILEMATCHING_API APuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APuzzleGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	class ATileGrid* CurrentTileGrid;

public:
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void SetCurrentTileGrid(ATileGrid* TileGrid);
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	ATileGrid* GetCurrentTileGrid();
	void OnClickTile(ATile* Tile);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	class UPlayerWidget* PlayerWidget;
};
