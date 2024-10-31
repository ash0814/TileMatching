// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.h"
#include "SwapTileCommand.generated.h"

/**
 * 
 */

class ATile;

UCLASS()
class TILEMATCHING_API USwapTileCommand : public UObject, public ICommand
{
	GENERATED_BODY()
	
private:
	class ATile* TileA;
	class ATile* TileB;

	FVector TileAOriginalLocation;
	FVector TileBOriginalLocation;

	int32 TileAOriginalIndexX;
	int32 TileAOriginalIndexY;
	int32 TileBOriginalIndexX;
	int32 TileBOriginalIndexY;

public:
	void Initialize(class ATile* InTileA, class ATile* InTileB);

	virtual void Execute() override;
	virtual void Undo() override;
};
