// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickupActor.h"
#include "MyPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePickupActor::ABasePickupActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ABasePickupActor::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
}

void ABasePickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<AMyPlayerCharacter>(OtherActor);
    if (!Pawn)return;
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

// Called every frame
void ABasePickupActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABasePickupActor::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ABasePickupActor::PickupWasTaken()
{
    Destroy();
    //CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    //if (GetRootComponent())
    //{
    //    GetRootComponent()->SetVisibility(false, true);
    //}

    //GetWorldTimerManager().SetTimer(RespawnTimerHandle, this,&ABasePickupActor::Respawn, RespawnTime);
}

void ABasePickupActor::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
    GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
}
