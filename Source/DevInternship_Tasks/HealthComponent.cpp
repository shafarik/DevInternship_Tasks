// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UHealthComponent::PickupHeal(int32 HealthAmount)
{
    if (Health == MaxHealth)
        return false;

    SetHealth(Health + HealthAmount);
    return true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
    }
}

void UHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChenged.Broadcast(Health, HealthDelta);
}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0 || IsDead() || !GetWorld())
        return;
    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
                                         UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                                         const UDamageType* DamageType, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}
