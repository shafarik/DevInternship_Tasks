// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyBaseWeapon.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
class UStaticMesh;
class UMyWeaponComponent;
class UHealthComponent;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{

    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UStaticMesh* WeaponMesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UStaticMesh* ProjectileMesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<AMyBaseWeapon> WeaponClasses;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0.01, ClampMax = 1))
    float FireRate;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float DamageAmount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float StartingAmmo;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName MuzzleSocketName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName WeaponSocketName;
};

UCLASS()
class DEVINTERNSHIP_TASKS_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMyCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCharacterMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UMyWeaponComponent* WeaponComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
   TArray<UAnimMontage*> AnimMontageArr;

    float InputLongitude = 0.0f;
    float InputLatitude = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.1, ClampMax = 1))
    float RotationSpeed = 0.7;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 1, ClampMax = 20))
    float ZoomingMultiplayer = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 1, ClampMax = 10))
    float ZoomingStep = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float MinZoomDistance = 400;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float MaxZoomDistance = 1500;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.01, ClampMax = 1))
    float RotationTreshold = 0.05;

private:
    void MoveForward(float value);

    void MoveRight(float value);

    void RotateCamera(float value);

    void LookAround(float Value);

    void ZoomCamera();
    void UnZoomCamera();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* WeaponDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FName> Inventory;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void OnDeath();
    virtual void OnHealthChanged(float Health, float HealthDelta);
    virtual void Destroyed() override;

    int32 GetMuzzle();
};
