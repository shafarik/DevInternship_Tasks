// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupActor.generated.h"

class USphereComponent;
UCLASS()
class DEVINTERNSHIP_TASKS_API ABasePickupActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABasePickupActor();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    FTimerHandle RespawnTimerHandle;


    virtual bool GivePickupTo(APawn* PlayerPawn);
    void PickupWasTaken();
    void Respawn();
};
