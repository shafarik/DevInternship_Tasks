// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseWeapon.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API UMyPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPersent();

        UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FAmmoData& AmmoData)const;

            UFUNCTION(BlueprintCallable, Category = "UI")
    float GetWeaponUIData()const;
};
