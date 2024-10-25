// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Command.h"
#include "TileCommandInvoker.generated.h"

UCLASS()
class TILEMATCHING_API ATileCommandInvoker : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<ICommand *> CommandStack;

public:
	void ExecuteCommand(ICommand * Command);
	void UndoCommand();
};
