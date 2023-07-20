// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PlayerLocationTask.generated.h"

UCLASS()
class DEVINTERNSHIP_TASKS_API UPlayerLocationTask : public UBTTaskNode
{
    GENERATED_BODY()
protected:
    UPlayerLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerActorKey;

};
