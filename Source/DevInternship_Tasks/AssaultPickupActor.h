// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickupActor.h"
#include "AssaultPickupActor.generated.h"

/**
 * 
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API AAssaultPickupActor : public ABasePickupActor
{
	GENERATED_BODY()
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
