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

    // 마우스 클릭 이벤트 활성화
    bEnableClickEvents = true;

    // 마우스 오버 이벤트 활성화
    bEnableMouseOverEvents = true;

    // 마우스 커서를 구속하지 않도록 설정 (필요한 경우)
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
    FVector End = Start + FVector(0, 0, -1) * 10000.0f; // 10,000 유닛 거리까지 트레이스

    FHitResult HitResult;
    FCollisionQueryParams Params;
    //Params.AddIgnoredActor(GetPawn()); // 플레이어 자신은 무시

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
