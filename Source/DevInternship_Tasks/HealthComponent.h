// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEVINTERNSHIP_TASKS_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    bool PickupHeal(int32 HealthAmount);
    void SetHealth(float NewHealth);
    float GetHealth() const
    {
        return Health;
    }
    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPrecent() const
    {
        return Health / MaxHealth;
    }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChenged;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

private:
    float Health = 0.0f;


    void ApplyDamage(float Damage, AController* InstigatedBy);

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
                           class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                           const class UDamageType* DamageType, AActor* DamageCauser);
};
