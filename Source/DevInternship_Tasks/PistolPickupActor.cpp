// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolPickupActor.h"
#include "MyPlayerCharacter.h"
#include "MyWeaponComponent.h"

bool APistolPickupActor::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogTemp, Display, TEXT("Pistol Acquired"));
    const auto Player=Cast<AMyPlayerCharacter>(PlayerPawn);
    if (!Player)return false;
    const auto Component = PlayerPawn->GetComponentByClass(UMyWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
    if (!WeaponComponent)return false;

    WeaponComponent->EquipSeccondaryWeapon();
    return true;
}
