// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseWeapon.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API UMySaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    int32 SavedCurrentWeaponIndex = 2;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<AMyBaseWeapon*> SavedWeapons;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    int32 SavedBullets = 0;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    float SavedHealth = 0.0f;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    FTransform SavedTransform;

        UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<int32> SavedInt;
};
