// Fill out your copyright notice in the Description page of Project Settings.

#include "MySettingsWidget.h"
#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/GameUserSettings.h"
#include "MyGameModeBase.h"
#include "Components/ComboBoxString.h"

void UMySettingsWidget::BackFromSettings()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;
    GameMode->BackFromSettings();
}

void UMySettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMySettingsWidget::OnChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UE_LOG(LogTemp, Display, TEXT("Is chenged"));
}
