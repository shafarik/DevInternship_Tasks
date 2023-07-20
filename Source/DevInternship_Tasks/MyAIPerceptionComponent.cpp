// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIPerceptionComponent.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyPlayerCharacter.h"
#include "AICharacter.h"
#include "Perception/AISense_Sight.h"

AActor* UMyAIPerceptionComponent::GetPlayerCharacter()
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
        return nullptr;

    const auto Controller = Cast<AMyAIController>(GetOwner());
    if (!Controller)
        return nullptr;
    //  const auto aicharacter=  Controller->GetOwner();
    // aicharacter->GetActorLocation();
    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    AActor* Character = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto PlayerActor = Cast<AMyPlayerCharacter>(PercieveActor);
        if (!PlayerActor)
        {
            continue;
        }
        else

        {
            Character = PlayerActor;
        }
    }
    return Character;
}

FVector UMyAIPerceptionComponent::GetMainLocation()
{
    const auto Controller = Cast<AMyAIController>(GetOwner());
    if (!Controller)
    {
        UE_LOG(LogTemp, Display, TEXT("controller not valid"));
        return FVector::ZeroVector;
    }
    const auto AiCharacter = Cast<AAICharacter>(Controller->GetPawn());
    if (!AiCharacter)

    {
        UE_LOG(LogTemp, Display, TEXT("aicharacter not valid"));
        return FVector::ZeroVector;
    }
   // UE_LOG(LogTemp, Display, TEXT("evetything is  valid"));
    return AiCharacter->GetActorLocation();
}

FVector UMyAIPerceptionComponent::GetPlayerLocation()
{
    if (!GetPlayerCharacter())
    {
     //   UE_LOG(LogTemp, Display, TEXT("PlayerCharacter is not valid"));
        return FVector::ZeroVector;
    }
    return GetPlayerCharacter()->GetActorLocation();
}

float UMyAIPerceptionComponent::Distance()
{
    return FVector::Distance(GetMainLocation(),GetPlayerLocation());
}
