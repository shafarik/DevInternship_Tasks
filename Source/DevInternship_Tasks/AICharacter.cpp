// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "MyGameModeBase.h"
#include "MyAIController.h"
#include "MyAIPerceptionComponent.h"
#include "BasePickupActor.h"
#include "BrainComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AMyAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}
void AAICharacter::ApplyDamage()
{
    float BaseDamage = 1.0f;

    // const auto Controller = Cast<AMyAIController>(GetController());
    // if (!Controller)
    //    return;
    // UE_LOG(LogTemp, Display, TEXT("Damage Is Cauting"));
    const auto Component = GetController()->GetComponentByClass(UMyAIPerceptionComponent::StaticClass());
    const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Component);
    if (!PerceptionComponent)
        return;
    FHitResult HitResult;

    UGameplayStatics::ApplyPointDamage(            //
        PerceptionComponent->GetPlayerCharacter(), //
        BaseDamage,                                //
        FVector::ZeroVector,                       //
        HitResult,                                 //
        GetControllers(),                          //
        this,                                      //
        UDamageType::StaticClass()                 //
    );
}
AController* AAICharacter::GetControllers() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void AAICharacter::OnDeath()
{
    Super::OnDeath();

    OnAIDestroyed.Broadcast();

    const auto MyController = Cast<AMyAIController>(Controller);
    if (MyController && MyController->BrainComponent)
    {
        MyController->BrainComponent->Cleanup();
    }
}

void AAICharacter::Destroyed()
{
    // UE_LOG(LogTemp, Display, TEXT("Destroyed is called"));
    FVector Location = this->GetActorLocation();
    FRotator Rotator = FRotator::ZeroRotator;
    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    if (FMath::FRand() <= 0.25)
    {
        GetWorld()->SpawnActor<ABasePickupActor>(HealthPickupClass, Location, Rotator, SpawnParam);
    }
    else if (FMath::FRand() <= 0.2)
    {
        GetWorld()->SpawnActor<ABasePickupActor>(AmmoPickupClass, Location, Rotator, SpawnParam);
    }
}
