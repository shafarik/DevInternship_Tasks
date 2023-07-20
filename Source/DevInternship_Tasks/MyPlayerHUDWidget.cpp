// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerHUDWidget.h"
#include "MyWeaponComponent.h"
#include "HealthComponent.h"

float UMyPlayerHUDWidget::GetHealthPersent()
{
    const auto Player =GetOwningPlayerPawn();
    if (!Player)return 0.0f;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)return 0.0f;

    return HealthComponent->GetHealthPrecent();
}

bool UMyPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto Player=GetOwningPlayerPawn();
    if (!Player)return false;

    const auto Component = Player->GetComponentByClass(UMyWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
    if (!WeaponComponent)return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

float UMyPlayerHUDWidget::GetWeaponUIData() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0;

    const auto Component = Player->GetComponentByClass(UMyWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
    if (!WeaponComponent)
        return 0;

    return WeaponComponent->GetWeaponUIData();
}
