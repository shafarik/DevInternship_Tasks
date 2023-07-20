// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseWeapon.generated.h"

class UStaticMeshComponent;
class AMyProjectile;
class UParticleSystem;
class UParticleSystemComponent;
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

//USTRUCT(BlueprintType)
//struct FWeaponUIData
//{
//    GENERATED_USTRUCT_BODY()
//
//    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
//    UTexture2D* MainIcon;
//};
UCLASS()
class DEVINTERNSHIP_TASKS_API AMyBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyBaseWeapon();

    FAmmoData GetAmmoData() const
    {
        return CurrentAmmo;
    }

    //FWeaponUIData GetUIData() const
    //{
    //    return UIData;
    //}

    void StartFire();
    void MakeShot();
    void StopFire();
    void InitMuzzleFX();
    void DecreaseAmmo();
    bool IsAmmoEmpty();
    void LogAmmo();
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeDamage(const FHitResult& HitResult);
    AController* GetController() const;
    FVector GetMuzzleWorldLocation() const;
    void SetAmmoData(int32 NewAmmoData)
    {
    CurrentAmmo.Bullets=NewAmmoData;
    }
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UParticleSystemComponent* SpawnMuzzleFX();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UStaticMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AMyProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UParticleSystem* MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{30, false};

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    //FWeaponUIData UIData;

    FTimerHandle ShotTimerHandle;

private:
    FAmmoData CurrentAmmo;

};
