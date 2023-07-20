// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

USTRUCT(BlueprintType) struct FGameData
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayersNum = 2;
};

UENUM(BlueprintType)
enum class EMatchState : uint8
{
    WaitToStart = 0,
    InProgress,
    Pause,
    Setting
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);

class AMyAIController;
UCLASS() class DEVINTERNSHIP_TASKS_API AMyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    AMyGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    FTimerHandle BotSpawnTimerHandle;

    virtual void StartPlay() override;
    virtual void BeginPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

    virtual bool ClearPause() override;
    void GoToSettings();
    void BackFromSettings();

    EMatchState GetMatchState() const
    {
    return MatchState;
    } 

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AMyAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerActorKey;

    float AINum;

private:
    EMatchState MatchState = EMatchState::WaitToStart;

    void SpawnBots();
    void StartSpawning();
    void DecreaseAiNum();

    void SetMatchState(EMatchState State);
};
