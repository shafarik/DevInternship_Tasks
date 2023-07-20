// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseWeapon.h"
#include "MyWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "MyProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyBaseWeapon::AMyBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AMyBaseWeapon::StartFire()
{
  //  if (!this)return;
    const auto Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return;

    const auto Component = Character->GetComponentByClass(UMyWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UMyWeaponComponent>(Component);
    if (!WeaponComponent)return;

    if (WeaponComponent->GetCurrentWeaponIndex()==2)return;

        static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AMyBaseWeapon::MakeShot, WeaponInfo->FireRate, true);
    MakeShot();
}

void AMyBaseWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const auto Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return;
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AMyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMyProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    InitMuzzleFX();
    DecreaseAmmo();
}

void AMyBaseWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AMyBaseWeapon::InitMuzzleFX()
{
    const auto Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return;
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    FVector SocketLocation = Character->GetMesh()->GetSocketLocation(WeaponInfo->MuzzleSocketName);
    FRotator SocketRotation = Character->GetMesh()->GetSocketRotation(WeaponInfo->MuzzleSocketName);
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFX, SocketLocation, SocketRotation, true, EPSCPoolMethod::AutoRelease, true);
}

void AMyBaseWeapon::DecreaseAmmo()
{
    if (!CurrentAmmo.Infinite)
        CurrentAmmo.Bullets--;
    LogAmmo();
}

bool AMyBaseWeapon::IsAmmoEmpty()
{
    return CurrentAmmo.Bullets == 0 && !CurrentAmmo.Infinite;
}

void AMyBaseWeapon::LogAmmo()
{
    FString AmmoInf = "Ammo " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInf += CurrentAmmo.Infinite ? "Infinite" : "Not infinite";
    UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInf);
}

void AMyBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

bool AMyBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{

    const auto Character = Cast<AMyCharacter>(GetOwner());
    if (!Character)
        return false;
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    TraceStart = GetMuzzleWorldLocation();
    FRotator ViewRotation = Character->GetMesh()->GetSocketRotation(WeaponInfo->WeaponSocketName);
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}
void AMyBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
    // const auto DamagedActor = HitResult.GetActor();
    // const auto Character = Cast<AMyCharacter>(GetOwner());
    // if (!DamagedActor || !Character)
    //     return;

    // FPointDamageEvent PointDamageEvent;
    // PointDamageEvent.HitInfo = HitResult;
    // static const FString ContexString(TEXT("Player Weapon info"));
    // TSubclassOf<UMyWeaponComponent> WeaponComponent;
    // const auto MyWeaponComponent = Cast<UMyWeaponComponent>(Character->GetComponentByClass(WeaponComponent));
    // FWeaponInfo* WeaponInfo =
    //     Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    // DamagedActor->TakeDamage(WeaponInfo->DamageAmount, PointDamageEvent, GetController(), this);
    // UE_LOG(LogTemp, Display, TEXT("actor is damaged"));
}

AController* AMyBaseWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

FVector AMyBaseWeapon::GetMuzzleWorldLocation() const
{
    const auto Character = Cast<AMyCharacter>(GetOwner());
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    return Character->GetMesh()->GetSocketLocation(WeaponInfo->MuzzleSocketName);
}

// Called when the game starts or when spawned
void AMyBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = DefaultAmmo;
}

// Called every frame
void AMyBaseWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UParticleSystemComponent* AMyBaseWeapon::SpawnMuzzleFX()
{
    const auto Character = Cast<AMyCharacter>(GetOwner());
    static const FString ContexString(TEXT("Player Weapon info"));
    FWeaponInfo* WeaponInfo =
        Character->WeaponDataTable->FindRow<FWeaponInfo>(Character->Inventory[Character->GetMuzzle()], ContexString, true);
    FVector SocketLocation = Character->GetMesh()->GetSocketLocation(WeaponInfo->MuzzleSocketName);
    FRotator SocketRotation = Character->GetMesh()->GetSocketRotation(WeaponInfo->MuzzleSocketName);
    return UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFX, SocketLocation, SocketRotation, true, EPSCPoolMethod::AutoRelease,
                                                    true);
}
