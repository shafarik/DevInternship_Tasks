// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySaveWidget.generated.h"

class UButton;
UCLASS()
class DEVINTERNSHIP_TASKS_API UMySaveWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* SaveButton;

    virtual void NativeOnInitialized() override;

public:
    UFUNCTION()
    void SaveProgress();
};
