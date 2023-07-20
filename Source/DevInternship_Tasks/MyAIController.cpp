// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "AICharacter.h"
#include "MyAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
    MyAIPerceptionComponent = CreateDefaultSubobject<UMyAIPerceptionComponent>("MyAIPerseptionComponent");
    SetPerceptionComponent(*MyAIPerceptionComponent);
}

void AMyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<AAICharacter>(InPawn);
    if (AICharacter)
    {
    RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void AMyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusedActor();
    //if (AimActor)
    //{
    //FVector AimVector = AimActor->GetActorLocation();
    //UE_LOG(LogTemp, Display, TEXT("%f,%f,%f"), AimVector.X, AimVector.Y, AimVector.Z);
    //}

    SetFocus(AimActor);
}



AActor* AMyAIController::GetFocusedActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FokusOnKeyName));
}

FVector AMyAIController::GetPlayerLocation()
{
    const auto AimActor = MyAIPerceptionComponent->GetPlayerCharacter();
    if (AimActor)
    {
    FVector AimVector = AimActor->GetActorLocation();
  //  UE_LOG(LogTemp, Display, TEXT("%f,%f,%f"), AimVector.X, AimVector.Y, AimVector.Z);
    return AimVector;
    }
    return FVector::ZeroVector;
}
