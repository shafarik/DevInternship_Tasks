// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerService.generated.h"

/**
 * 
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API UFindPlayerService : public UBTService
{
	GENERATED_BODY()
	
	public:

	    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerActorKey;


    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
