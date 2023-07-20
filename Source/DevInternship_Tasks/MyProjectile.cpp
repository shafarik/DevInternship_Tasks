// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectile.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(10.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SphereComponent->bReturnMaterialOnMove = true;
    SetRootComponent(SphereComponent);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
    StaticMesh->AttachToComponent(SphereComponent,Rules);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(SphereComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SphereComponent->OnComponentHit.AddDynamic(this,&AMyProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld())return;
    const auto Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return;
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);

    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyPointDamage(OtherActor, WeaponInfo->DamageAmount, NormalImpulse,Hit,GetController(),this,UDamageType::StaticClass());
   FString Hited= OtherActor->GetName();
   // UE_LOG(LogTemp,Display,TEXT("name is %s"),*Hited);
    Destroy();
}

AController* AMyProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
