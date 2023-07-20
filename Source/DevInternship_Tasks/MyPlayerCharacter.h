// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API AMyPlayerCharacter : public AMyCharacter
{
	GENERATED_BODY()
	

	public:
    virtual void OnHealthChanged(float Health, float HealthDelta);
        virtual void Tick(float DeltaTime) override;
    virtual void OnDeath();
};
