// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameModeBase.h"
#include "PuzzlePlayerController.h"

APuzzleGameModeBase::APuzzleGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}
