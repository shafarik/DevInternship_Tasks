// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UMyAIPerceptionComponent;
UCLASS()
class DEVINTERNSHIP_TASKS_API AMyAIController : public AAIController
{
    GENERATED_BODY()

    public:
    AMyAIController();
        FVector GetPlayerLocation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UMyAIPerceptionComponent* MyAIPerceptionComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FokusOnKeyName = "PlayerActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor* GetFocusedActor()const;


};
