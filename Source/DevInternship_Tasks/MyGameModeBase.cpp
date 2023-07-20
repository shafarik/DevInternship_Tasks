// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "Engine/Engine.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "AICharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
    DefaultPawnClass = AMyCharacter::StaticClass();
}

void AMyGameModeBase::StartPlay()
{
    Super::StartPlay();

    SetMatchState(EMatchState::InProgress);
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    StartSpawning();
}

UClass* AMyGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool AMyGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(EMatchState::Pause);
    }

    return PauseSet;
}

bool AMyGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EMatchState::InProgress);
    }
    return PauseCleared;
}

void AMyGameModeBase::GoToSettings()
{
    SetMatchState(EMatchState::Setting);
}

void AMyGameModeBase::BackFromSettings()
{
    SetMatchState(EMatchState::Pause);
}

void AMyGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    if (AINum < GameData.PlayersNum - 1)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        PlayerActorKey.SelectedKeyName = "IsSpawned";
        const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);

        RestartPlayer(AIController);
        const auto Blackboard = AIController->GetBlackboardComponent();
        Blackboard->SetValueAsBool(PlayerActorKey.SelectedKeyName, true);
        const auto AICharacter = Cast<AAICharacter>(AIController->GetPawn());
        if (!AICharacter)
            return;
        AICharacter->OnAIDestroyed.AddUObject(this, &AMyGameModeBase::DecreaseAiNum);

        AINum++;
        UE_LOG(LogTemp, Display, TEXT("AiNum is %f"), AINum);
    }
    // else
    //{
    // GetWorldTimerManager().ClearTimer(BotSpawnTimerHandle);
    // }
}

void AMyGameModeBase::StartSpawning()
{
    GetWorldTimerManager().SetTimer(BotSpawnTimerHandle, this, &AMyGameModeBase::SpawnBots, 3.0f, true);
}

void AMyGameModeBase::DecreaseAiNum()
{
    AINum--;
    UE_LOG(LogTemp, Display, TEXT("AiNum decreased to %f"), AINum);
    // StartSpawning();
}

void AMyGameModeBase::SetMatchState(EMatchState State)
{
    if (MatchState == State)
        return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
