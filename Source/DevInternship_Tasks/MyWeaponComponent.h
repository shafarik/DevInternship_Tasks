// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "MyWeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEVINTERNSHIP_TASKS_API UMyWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UMyWeaponComponent();

protected:
    int32 CurrentWeaponIndex = 0;

    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY()
    AMyBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AMyBaseWeapon*> Weapons = {nullptr, nullptr};

public:
    // UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    // TArray<FName> Inventory;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void StartFire();
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
    void StopFire();
    void ChangeWeapon();
    void EquipMainWeapon();
    void HasNoWeapon();
    void EquipSeccondaryWeapon();
    void SwapToMainWeapon();
    void SwapToSeccondaryWeapon();
    void EquipWeapon(int32 WeaponIndex);
    UFUNCTION(BlueprintCallable)
    int32 GetCurrentWeaponIndex()
    {
        return CurrentWeaponIndex;
    }
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
    float GetWeaponUIData() const;
    TArray<AMyBaseWeapon*> GetWeaponsArray() const
    {
        return Weapons;
    }
    void SetWeaponsArray(TArray<AMyBaseWeapon*> NewWeapons,TArray<int32> IntArray);

    void SetCurrentWEaponIndex(int32 NewWeaponIndex)
    {
    CurrentWeaponIndex=NewWeaponIndex;
    EquipWeapon(CurrentWeaponIndex);
    }
    void SetWeaponsAmmo(int32 NewAmmo);

private:
    bool IsInventoryFull = false;

    void SpawnWeapons(int32 Index);
    void SpawnEquipWeapon(int32 Index);
    void SpawnArmoryWeapon(int32 Index);
    void AttachWeaponToSocket(AMyBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& ScoketName);
};
