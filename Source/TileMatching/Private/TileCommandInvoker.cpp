// Fill out your copyright notice in the Description page of Project Settings.


#include "TileCommandInvoker.h"

void ATileCommandInvoker::ExecuteCommand(ICommand * Command)
{
	Command->Execute();
	CommandStack.Push(Command);
}

void ATileCommandInvoker::UndoCommand()
{
	if (CommandStack.Num() > 0)
	{
		ICommand * Command = CommandStack.Last();
		Command->Undo();
		CommandStack.Pop();
	}
}
