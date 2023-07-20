// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(DamageLog,All,All);
void AMyPlayerCharacter::OnHealthChanged(float Health, float HealthDelta)
{
   // UE_LOG(LogTemp, Display, TEXT("Health is changed to %f, Damage is %f"), Health, HealthDelta);
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
    float HEalth = HealthComponent->GetHealth();
   // UE_LOG(DamageLog, Display, TEXT("health is %f"), HEalth);
}

void AMyPlayerCharacter::OnDeath()
{
Super::OnDeath();
UGameplayStatics::OpenLevel(GetWorld(),FName(GetWorld()->GetName()),false);
}
