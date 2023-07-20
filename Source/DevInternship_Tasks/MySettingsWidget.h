// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "MySettingsWidget.generated.h"

class UComboBoxString;
UCLASS()
class DEVINTERNSHIP_TASKS_API UMySettingsWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void BackFromSettings();

	virtual void NativeOnInitialized()override;
    UFUNCTION()
    void OnChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UPROPERTY()
    UComboBoxString* Compbobox;
};
