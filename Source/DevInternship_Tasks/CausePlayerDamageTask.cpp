// Fill out your copyright notice in the Description page of Project Settings.

#include "CausePlayerDamageTask.h"
#include "MyAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "AICharacter.h"
#include "GameFramework/Actor.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCausePlayerDamageTask::UCausePlayerDamageTask()
{
    NodeName = "Cause Damage To Player";
}

EBTNodeResult::Type UCausePlayerDamageTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
        return EBTNodeResult::Succeeded;

    const auto Component = Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass());
    const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Component);
    if (!PerceptionComponent)
        return EBTNodeResult::Succeeded;
    float Distance = PerceptionComponent->Distance();

    const auto Character = Cast<AAICharacter>(Controller->GetCharacter());
    // if (!Character)
    //     return EBTNodeResult::Succeeded;

    if (Distance < DistanceToCauseDamage)
    {
     //   UE_LOG(LogTemp, Display, TEXT("Distance is %f"), Distance);
        Character->GetWorldTimerManager().SetTimer(DamageCauseTimerHandle, Character, &AAICharacter::ApplyDamage, 0.5f, true);
        return EBTNodeResult::InProgress;
    }
    if (Distance >= DistanceToCauseDamage)
    {
        Character->GetWorldTimerManager().ClearTimer(DamageCauseTimerHandle);
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}
