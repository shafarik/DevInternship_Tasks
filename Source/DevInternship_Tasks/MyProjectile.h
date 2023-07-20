// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class DEVINTERNSHIP_TASKS_API AMyProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyProjectile();

    void SetShotDirection(const FVector& Direction)
    {
        ShotDirection = Direction;
    }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                         UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

                             AController* GetController() const;
};
