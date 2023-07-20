// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MyAIPerceptionComponent.generated.h"


UCLASS()
class DEVINTERNSHIP_TASKS_API UMyAIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:
    AActor* GetPlayerCharacter();
    FVector GetMainLocation();
    FVector GetPlayerLocation();
    float Distance();

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
    //AMyCharacter MyCharacter;
};
