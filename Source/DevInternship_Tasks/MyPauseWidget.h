// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPauseWidget.generated.h"

class UButton;
UCLASS()
class DEVINTERNSHIP_TASKS_API UMyPauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SaveGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* LoadGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

private:
    UFUNCTION()
    void OnClearPause();

    UFUNCTION()
    void SaveGame();

    UFUNCTION()
    void LoadGame();

    UFUNCTION()
    void Settings();

    UFUNCTION()
    void Quit();


};
