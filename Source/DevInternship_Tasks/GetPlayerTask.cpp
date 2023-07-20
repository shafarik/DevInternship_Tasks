// Fill out your copyright notice in the Description page of Project Settings.

#include "GetPlayerTask.h"
#include "MyCharacter.h"
#include "MyAIController.h"
#include "MyAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"

UGetPlayerTask::UGetPlayerTask()
{
    NodeName = "Get Player";
}

EBTNodeResult::Type UGetPlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
        return EBTNodeResult::Failed;

    // const auto Component = Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass());
    // const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Component);
    // if (!PerceptionComponent)
    //     return EBTNodeResult::Failed;
    // Blackboard->SetValueAsVector(PlayerActorKey.SelectedKeyName, PerceptionComponent->GetMainLocation());

    //   APlayerController* PlayerContoller=UGameplayStatics::GetPlayerCharacter(GetWorld(),0)

    ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AMyCharacter* PlayerCharacter=Cast<AMyCharacter>(Character);
    if (!PlayerCharacter)
        return EBTNodeResult::Failed;

        Blackboard->SetValueAsObject(PlayerCharacterKey.SelectedKeyName, PlayerCharacter);
    return EBTNodeResult::Succeeded;
}
