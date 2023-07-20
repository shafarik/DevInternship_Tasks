// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickupActor.h"
#include "PistolPickupActor.generated.h"

/**
 * 
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API APistolPickupActor : public ABasePickupActor
{
	GENERATED_BODY()
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
