// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CausePlayerDamageTask.generated.h"

/**
 *
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API UCausePlayerDamageTask : public UBTTaskNode
{
    GENERATED_BODY()

protected:
    UCausePlayerDamageTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DistanceToCauseDamage = 200.0f;

    FTimerHandle DamageCauseTimerHandle;
};
