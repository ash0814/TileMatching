// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	TT_Red UMETA(DisplayName = "Red"),
	TT_Green UMETA(DisplayName = "Green"),
	TT_Blue UMETA(DisplayName = "Blue"),
	TT_Yellow UMETA(DisplayName = "Yellow"),
	TT_Purple UMETA(DisplayName = "Purple"),
	TT_Orange UMETA(DisplayName = "Orange"),
	TT_Cyan UMETA(DisplayName = "Cyan"),
	TT_Magenta UMETA(DisplayName = "Magenta"),
	TT_None UMETA(DisplayName = "None")
};

UCLASS()
class TILEMATCHING_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Tile Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	class UBoxComponent* TileBoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tile")
	class UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	class UBoxComponent* SelectionBoxComp;

private:
	bool bIsSelected;
	int32 TileIndexX;
	int32 TileIndexY;

	ATileGrid* TileGrid;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ETileType TileType;
	UFUNCTION(BlueprintCallable, Category = "Getter")
	ETileType GetTileType() const { return TileType; }

	UFUNCTION(BlueprintCallable, Category = "Getter")
	bool GetIsSelected() const { return bIsSelected; }

	UFUNCTION(BlueprintCallable, Category = "Getter")
	void GetTileIndex(int32& OutX, int32& OutY) const;

	UFUNCTION(BlueprintCallable, Category = "Getter")
	ATileGrid* GetTileGrid() const { return TileGrid; }

// Setter
public:
	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetOutlineColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetTileColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetTileType(ETileType NewType);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetSelected(bool bSelected);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetTileIndex(int32 NewX, int32 NewY);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void SetTileGrid(ATileGrid* NewTileGrid) { TileGrid = NewTileGrid; }

public:

};
