// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultPickupActor.h"
#include "MyPlayerCharacter.h"
#include "MyWeaponComponent.h"

bool AAssaultPickupActor::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogTemp, Display, TEXT("Assault rifle Acquired"));
    const auto Player = Cast<AMyPlayerCharacter>(PlayerPawn);
    if (!Player)
        return false;
    const auto Component = PlayerPawn->GetComponentByClass(UMyWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
    if (!WeaponComponent)
        return false;

    WeaponComponent->EquipMainWeapon();
    return true;
}
