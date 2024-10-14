// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Tile.h"
#include "TileGrid.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	// spawn tile grid
	FActorSpawnParameters SpawnParams;
	if (TileClass)
		TileGrid = GetWorld()->SpawnActor<ATileGrid>(TileClass, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParams);
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

