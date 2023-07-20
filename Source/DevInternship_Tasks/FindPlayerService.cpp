// Fill out your copyright notice in the Description page of Project Settings.

#include "FindPlayerService.h"
#include "MyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto Component = Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass());
        const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Component);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, PerceptionComponent->GetPlayerCharacter());
        }
        Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }
}
