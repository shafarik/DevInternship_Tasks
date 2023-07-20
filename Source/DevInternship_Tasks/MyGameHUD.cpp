// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameHUD.h"
#include "MyGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMyGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EMatchState::Setting, CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass));

    for (auto GameWidgetPair: GameWidgets)
    {
    const auto GameWidget=GameWidgetPair.Value;
        if (!GameWidget)continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld())
    {
        const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this,&AMyGameHUD::OnMatchStateChanged);
        }
    }

}

void AMyGameHUD::OnMatchStateChanged(EMatchState State)
{
    if (CurrentWidget)
    {
    CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
    CurrentWidget = GameWidgets[State];
    }

        if (CurrentWidget)
    {
    CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
