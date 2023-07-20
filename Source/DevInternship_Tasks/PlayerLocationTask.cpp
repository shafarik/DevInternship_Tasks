// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerLocationTask.h"
#include "MyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

UPlayerLocationTask::UPlayerLocationTask()
{
    NodeName = "Set Main Location";
}

EBTNodeResult::Type UPlayerLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
        return EBTNodeResult::Failed;

    const auto Component = Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass());
    const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Component);
    if (!PerceptionComponent)
        return EBTNodeResult::Failed;
    Blackboard->SetValueAsVector(PlayerActorKey.SelectedKeyName, PerceptionComponent->GetMainLocation());

        return EBTNodeResult::Succeeded;
}
