// Fill out your copyright notice in the Description page of Project Settings.

#include "MyWeaponComponent.h"
#include "MyCharacter.h"
#include "Engine.h"
#include "MyBaseWeapon.h"

// Sets default values for this component's properties
UMyWeaponComponent::UMyWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UMyWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    //Weapons.Add(nullptr);
    //Weapons.Add(nullptr);
    CurrentWeaponIndex = 2;
    //SpawnEquipWeapon(CurrentWeaponIndex);
}

// Called every frame
void UMyWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UMyWeaponComponent::StartFire()
{
    if (!CurrentWeapon)return;
    CurrentWeapon->StartFire();
}

void UMyWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        if (!Weapon)continue;
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    UE_LOG(LogTemp, Display, TEXT("Weapon is destroyed"));
    Super::EndPlay(EndPlayReason);
}

void UMyWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void UMyWeaponComponent::ChangeWeapon()
{
    int32 NewWeaponIndex = CurrentWeaponIndex == 0 ? 1 : 0;
    EquipWeapon(NewWeaponIndex);
    CurrentWeaponIndex = NewWeaponIndex;
}

void UMyWeaponComponent::EquipMainWeapon()
{
    if (IsInventoryFull)
    {
        EquipWeapon(0);
        FAmmoData OldAmmoData=CurrentWeapon->GetAmmoData();
        CurrentWeapon->SetAmmoData(OldAmmoData.Bullets+30);
    }
    else
    {
        switch (CurrentWeaponIndex)
        {
        case 0:
            FAmmoData OldAmmoData = CurrentWeapon->GetAmmoData();
            CurrentWeapon->SetAmmoData(OldAmmoData.Bullets + 30);
            return;
            break;
        case 1:
            UE_LOG(LogTemp, Display, TEXT("SpawnArmory"));
            SpawnArmoryWeapon(0);
            break;
        case 2:
            UE_LOG(LogTemp, Display, TEXT("Spawnequip"));
            SpawnEquipWeapon(0);
            break;
        }
    }
}

void UMyWeaponComponent::HasNoWeapon()
{
}

void UMyWeaponComponent::EquipSeccondaryWeapon()
{
    if (IsInventoryFull)
    {
        EquipWeapon(1);
    }
    else
    {
        switch (CurrentWeaponIndex)
        {
        case 1:
            return;
            break;
        case 0:
            UE_LOG(LogTemp, Display, TEXT("SpawnArmory"));
            SpawnArmoryWeapon(1);
            break;
        case 2:
            UE_LOG(LogTemp, Display, TEXT("Spawnequip"));
            SpawnEquipWeapon(1);
            break;
        }
    }
}

void UMyWeaponComponent::SwapToMainWeapon()
{
    if (Weapons[0])
    {
    EquipWeapon(0);
    }
}

void UMyWeaponComponent::SwapToSeccondaryWeapon()
{
    if (Weapons[1])
    {
    EquipWeapon(1);
    }
}

void UMyWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
        return;
    }
    AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo = Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[WeaponIndex], ContexString, true);
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponInfo->WeaponSocketName);
    CurrentWeaponIndex = WeaponIndex;
}

bool UMyWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

float UMyWeaponComponent::GetWeaponUIData() const
{
    return CurrentWeaponIndex;
}

void UMyWeaponComponent::SetWeaponsArray(TArray<AMyBaseWeapon*> NewWeapons, TArray<int32> IntArray)
{
    if (NewWeapons[0] == nullptr && NewWeapons[1]==nullptr)
    {
        switch (IntArray.Num())
        {
        case 0:
            break;
        case 1:
            if (IntArray[0] == 0)
            {
         //   rifle
         SpawnWeapons(0);
            }
            else
            {
         //   pistol
         SpawnWeapons(1);
            }
            break;
        case 2:
        //both
        SpawnWeapons(0);
        SpawnWeapons(1);
            break;
        }
    }
    else
        Weapons = NewWeapons;
}

void UMyWeaponComponent::SetWeaponsAmmo(int32 NewAmmo)
{
    if (Weapons[0])
    {
        Weapons[0]->SetAmmoData(NewAmmo);
    }
}

void UMyWeaponComponent::SpawnWeapons(int32 Index)
{
    AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());
    if (!GetWorld() || !Character)
        return;
        static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo = Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Index], ContexString, true);
        auto Weapon = GetWorld()->SpawnActor<AMyBaseWeapon>(WeaponInfo->WeaponClasses);
        if (!Weapon)return;

        Weapon->SetOwner(Character);
        //Weapons.Add(Weapon);
        //CurrentWeapon = Weapon;
        Weapons[Index] = Weapon;
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);

        EquipWeapon(Index);
}

void UMyWeaponComponent::SpawnEquipWeapon(int32 Index)
{
    AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());
    if (!GetWorld() || !Character)
        return;

    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo = Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Index], ContexString, true);
    UE_LOG(LogTemp, Display, TEXT("%s"), *Character->Inventory[Index].ToString());
    auto Weapon = GetWorld()->SpawnActor<AMyBaseWeapon>(WeaponInfo->WeaponClasses);
    if (!Weapon)
        return;

    Weapon->SetOwner(Character);
   // Weapons.Add(Weapon);
    CurrentWeapon = Weapon;
    Weapons[Index] = Weapon;
    AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponInfo->WeaponSocketName);
    CurrentWeaponIndex = Index;
}

void UMyWeaponComponent::SpawnArmoryWeapon(int32 Index)
{
    AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());
    if (!GetWorld() || !Character)
        return;

    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo = Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Index], ContexString, true);
    auto Weapon = GetWorld()->SpawnActor<AMyBaseWeapon>(WeaponInfo->WeaponClasses);
    if (!Weapon)
        return;

    Weapon->SetOwner(Character);
   // Weapons.Add(Weapon);
    CurrentWeapon = Weapon;
    Weapons[Index] = Weapon;
    AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    EquipWeapon(Index);
    EquipWeapon(Index==1?0:1);
    EquipWeapon(Index);
    IsInventoryFull = true;
}

void UMyWeaponComponent::AttachWeaponToSocket(AMyBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& ScoketName)
{
    if (!Weapon || !SceneComponent)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, ScoketName);
}
