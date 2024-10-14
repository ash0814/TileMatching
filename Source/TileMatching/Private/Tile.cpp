// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TileBoxComp"));
	TileBoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 10.0f));
	SetRootComponent(TileBoxComp);

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Cube.Cube'")).Object);
	//TileType = static_cast<ETileType>(FMath::RandRange(0, 3));
	TileMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 0.2f));
	TileMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	TileMesh->SetupAttachment(TileBoxComp);

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetTileType(ETileType NewType)
{
	TileType = NewType;
	switch (TileType)
	{
	case ETileType::TT_Red:
		SetTileColor(FLinearColor::Red);
		break;
	case ETileType::TT_Green:
		SetTileColor(FLinearColor::Green);
		break;
	case ETileType::TT_Blue:
		SetTileColor(FLinearColor::Blue);
		break;
	case ETileType::TT_Yellow:
		SetTileColor(FLinearColor::Yellow);
		break;
	default:
		break;
	}
}

void ATile::SetTileColor(FLinearColor NewColor)
{
	FVector NewColorVec = FVector(NewColor.R, NewColor.G, NewColor.B);
	TileMesh->SetVectorParameterValueOnMaterials(FName("Color"), NewColorVec);
	TileMesh->SetScalarParameterValueOnMaterials(FName("Opacity"), NewColor.A);
}

void ATile::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;
	if (bIsSelected)
	{
		SetTileColor(FLinearColor::White);
	}
	else
	{
		SetTileType(TileType);
	}
}

