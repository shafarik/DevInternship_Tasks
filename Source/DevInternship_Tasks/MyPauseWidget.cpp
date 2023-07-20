// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPauseWidget.h"
#include "MySaveGame.h"
#include "MyPlayerCharacter.h"
#include "Gameframework/GameModeBase.h"
#include "HealthComponent.h"
#include "MyWeaponComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "MyGameModeBase.h"

bool UMyPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UMyPauseWidget::OnClearPause);
    }
    if (SaveGameButton)
    {
        SaveGameButton->OnClicked.AddDynamic(this, &UMyPauseWidget::SaveGame);
    }
    if (LoadGameButton)
    {
        LoadGameButton->OnClicked.AddDynamic(this, &UMyPauseWidget::LoadGame);
    }
    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UMyPauseWidget::Settings);
    }
    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMyPauseWidget::Quit);
    }

    return InitStatus;
}

void UMyPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void UMyPauseWidget::SaveGame()
{
    GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("GameSaved"));
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    if (!GetWorld())
        return;
    const auto Character = Cast<AMyPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (Character)
    {
        const auto Component = Character->GetComponentByClass(UMyWeaponComponent::StaticClass());
        const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
        if (!WeaponComponent)
            return;

        const auto HComponent = Character->GetComponentByClass(UHealthComponent::StaticClass());
        const auto HealthComponent = Cast<UHealthComponent>(HComponent);
        if (!HealthComponent)
            return;

        SaveGameInstance->SavedCurrentWeaponIndex = WeaponComponent->GetCurrentWeaponIndex();
        TArray<AMyBaseWeapon*> SavedWeapons = WeaponComponent->GetWeaponsArray();

        if (!SavedWeapons[0])
            GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("Weapon0 is null"));
        if (!SavedWeapons[1])
            GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("Weapon1 is null"));

        for (int32 i = 0; i < SavedWeapons.Num(); ++i)
        {
            if (SavedWeapons[i])
            SaveGameInstance->SavedInt.Add(i);
        }
        SaveGameInstance->SavedWeapons = SavedWeapons;
        if (SavedWeapons[0])
        {
            FAmmoData SavedAmmoData = SavedWeapons[0]->GetAmmoData();
            SaveGameInstance->SavedBullets = SavedAmmoData.Bullets;
        }
        SaveGameInstance->SavedHealth = HealthComponent->GetHealth();
        FTransform CharacterTransform = Character->GetActorTransform();
        SaveGameInstance->SavedTransform = CharacterTransform;
    }

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot_0"), 0);

    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void UMyPauseWidget::LoadGame()
{
    GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("GameLoaded"));

    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot_0"), 0));

    if (SaveGameInstance)
    {
        if (!GetWorld())
            return;
        const auto Character = Cast<AMyPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
        if (Character)
        {
            const auto Component = Character->GetComponentByClass(UMyWeaponComponent::StaticClass());
            const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
            if (!WeaponComponent)
                return;

            const auto HComponent = Character->GetComponentByClass(UHealthComponent::StaticClass());
            const auto HealthComponent = Cast<UHealthComponent>(HComponent);
            if (!HealthComponent)
                return;

            HealthComponent->SetHealth(SaveGameInstance->SavedHealth);
            WeaponComponent->SetWeaponsArray(SaveGameInstance->SavedWeapons, SaveGameInstance->SavedInt);
            WeaponComponent->SetCurrentWEaponIndex(SaveGameInstance->SavedCurrentWeaponIndex);
            WeaponComponent->SetWeaponsAmmo(SaveGameInstance->SavedBullets);
            Character->SetActorTransform(SaveGameInstance->SavedTransform);

            //WeaponComponent->EquipWeapon(SaveGameInstance->SavedCurrentWeaponIndex == 1 ? 0 : 1);
           // WeaponComponent->EquipWeapon(SaveGameInstance->SavedCurrentWeaponIndex);

            if (!GetWorld() || !GetWorld()->GetAuthGameMode())
                return;

            GetWorld()->GetAuthGameMode()->ClearPause();
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("No save exists"));
    }
}

void UMyPauseWidget::Settings()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;
    GameMode->GoToSettings();
}

void UMyPauseWidget::Quit()
{
    GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("Quit"));
}
