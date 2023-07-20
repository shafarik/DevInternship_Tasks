// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetPlayerTask.generated.h"

/**
 *
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API UGetPlayerTask : public UBTTaskNode
{
    GENERATED_BODY()

protected:
    UGetPlayerTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerCharacterKey;
};
