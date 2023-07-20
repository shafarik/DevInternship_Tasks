// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "AICharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAIDestroyed);

class UBehaviorTree;
class ABasePickupActor;

UCLASS()
class DEVINTERNSHIP_TASKS_API AAICharacter : public AMyCharacter
{
    GENERATED_BODY()

    AAICharacter(const FObjectInitializer& ObjInit);

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp")
    TSubclassOf<ABasePickupActor> HealthPickupClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp")
    TSubclassOf<ABasePickupActor> AmmoPickupClass;

public:
    void ApplyDamage();

    AController* GetControllers() const;
    virtual void OnDeath() override;
    virtual void Destroyed() override;

    FOnAIDestroyed OnAIDestroyed;
};
