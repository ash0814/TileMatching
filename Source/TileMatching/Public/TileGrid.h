// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Number of tiles in the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 SideLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	float TileSpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	TSubclassOf<class ATile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	TArray<class ATile*> TileGrid;

	UFUNCTION(BlueprintCallable, Category = "Tile Grid")
	void GenerateGrid();
};
