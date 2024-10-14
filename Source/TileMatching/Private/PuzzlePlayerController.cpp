// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "TileGrid.h"
#include "Tile.h"


APuzzlePlayerController::APuzzlePlayerController()
{
}

void APuzzlePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(this)) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem
            = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
            (PlayerController->GetLocalPlayer())) {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
        }
    }

    bShowMouseCursor = true;

    // ���콺 Ŭ�� �̺�Ʈ Ȱ��ȭ
    bEnableClickEvents = true;

    // ���콺 ���� �̺�Ʈ Ȱ��ȭ
    bEnableMouseOverEvents = true;

    // ���콺 Ŀ���� �������� �ʵ��� ���� (�ʿ��� ���)
    SetInputMode(FInputModeGameAndUI());
}

void APuzzlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = 
        Cast<UEnhancedInputComponent>(InputComponent))
    {
		EnhancedInputComponent->BindAction(IA_Click, ETriggerEvent::Started, this, &APuzzlePlayerController::OnLeftClick);
    }
}

void APuzzlePlayerController::OnLeftClick(const FInputActionValue& Value)
{
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector Start = WorldLocation;
    FVector End = Start + FVector(0, 0, -1) * 10000.0f; // 10,000 ���� �Ÿ����� Ʈ���̽�

    FHitResult HitResult;
    FCollisionQueryParams Params;
    //Params.AddIgnoredActor(GetPawn()); // �÷��̾� �ڽ��� ����

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
    if (bHit && HitResult.GetActor())
    {
        AActor* HitActor = HitResult.GetActor();
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()));
        
        if (ATile* HitTile = Cast<ATile>(HitActor))
		{
            HitTile->SetSelected(true);
		}
    }
}
