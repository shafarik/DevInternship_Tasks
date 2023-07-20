// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyGameModeBase.h"
#include "GameFramework/GameModeBase.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AMyPlayerController::OnMatchStateChanged);
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &AMyPlayerController::OnPauseGame);
}

void AMyPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;
    const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)return;
    if (GameMode->GetMatchState()==EMatchState::Pause)
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
    }
    else
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);
    }

}

void AMyPlayerController::OnMatchStateChanged(EMatchState State)
{
    if (State==EMatchState::InProgress)
    {
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor=false;
    }
    else
    {
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor=true;
    }
}
