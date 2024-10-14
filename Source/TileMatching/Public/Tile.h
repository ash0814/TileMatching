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

private:
	bool bIsSelected;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ETileType TileType;
	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SetTileType(ETileType NewType);

	UFUNCTION(BlueprintCallable, Category = "Tile")
	ETileType GetTileType() const { return TileType; }

	UFUNCTION(BlueprintCallable)
	void SetTileColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
	void SetSelected(bool bSelected);


};
