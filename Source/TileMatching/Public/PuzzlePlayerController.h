// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzlePlayerController.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;
class AGameManager;

UCLASS()
class TILEMATCHING_API APuzzlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APuzzlePlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* IA_Click;
	
	UFUNCTION()
	void OnLeftClick(const FInputActionValue& Value);
};
