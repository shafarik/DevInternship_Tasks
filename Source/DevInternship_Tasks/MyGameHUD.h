// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameModeBase.h"
#include "GameFramework/HUD.h"
#include "MyGameHUD.generated.h"

/**
 *
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API AMyGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> SettingsWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<EMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget=nullptr;

    void OnMatchStateChanged(EMatchState State);
};
