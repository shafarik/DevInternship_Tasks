// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MyWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Camera/CameraComponent.h"
#include "HealthComponent.h"
#include "Engine/GameViewportClient.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values

AMyCharacter::AMyCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("MovementComponent");

    WeaponComponent = CreateDefaultSubobject<UMyWeaponComponent>("WeaponComponent");

    HealthComponent=CreateDefaultSubobject<UHealthComponent>("HealthComopnent");
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);

    HealthComponent->OnDeath.AddUObject(this, &AMyCharacter::OnDeath);
    HealthComponent->OnHealthChenged.AddUObject(this, &AMyCharacter::OnHealthChanged);
}

void AMyCharacter::MoveForward(float value)
{
    if (value == 0)
        return;
    AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value)
{
    if (value == 0)
        return;
    AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::RotateCamera(float value)
{
    if (value == 0)
        return;
    AddControllerYawInput(value * RotationSpeed);
}

void AMyCharacter::LookAround(float Value)
{
    AddControllerYawInput(Value);
}

void AMyCharacter::OnDeath()
{
//UE_LOG(LogTemp,Display,TEXT("AI Is Dead"));
    PlayAnimMontage(AnimMontageArr[FMath::RandRange(0,2)]);

    SetLifeSpan(3.0f);
   // GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetCharacterMovement()->DisableMovement();
    WeaponComponent->StopFire();
}

void AMyCharacter::OnHealthChanged(float Health, float HealthDelta)
{
   // UE_LOG(LogTemp, Display, TEXT("Health Was Changed"));
}

void AMyCharacter::Destroyed()
{
  //  WeaponComponent->EndPlay(EEndPlayReason::Destroyed);
}

void AMyCharacter::ZoomCamera()
{
    float OldTargetArmLenght = SpringArmComponent->TargetArmLength;
    float NewArgetArmLenght = FMath::Clamp(OldTargetArmLenght - ZoomingStep * ZoomingMultiplayer, MinZoomDistance, MaxZoomDistance);
    SpringArmComponent->TargetArmLength = NewArgetArmLenght;
}

void AMyCharacter::UnZoomCamera()
{
    float OldTargetArmLenght = SpringArmComponent->TargetArmLength;
    float NewArgetArmLenght = FMath::Clamp(OldTargetArmLenght + ZoomingStep * ZoomingMultiplayer, MinZoomDistance, MaxZoomDistance);
    SpringArmComponent->TargetArmLength = NewArgetArmLenght;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //const auto Health=HealthComponent->GetHealth();
    //UE_LOG(LogTemp, Display, TEXT("%.0f"),Health);

   // TakeDamage(0.1f, FDamageEvent{},Controller,this);


    // UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();

    // FVector2D MousePosition;
    // ViewportClient->GetMousePosition(MousePosition);

    // FVector2D ViewportSize;
    // ViewportClient->GetViewportSize(ViewportSize);

    // FVector2D CursorPosition = MousePosition - ViewportSize;

    // float CloseToEdgesValue = ViewportSize.X * RotationTreshold;

    // if (CursorPosition.X * -1 >= ViewportSize.X)
    //     return;

    // if (CursorPosition.X * -1 > ViewportSize.X - CloseToEdgesValue)
    //{
    //       UE_LOG(LogTemp, Display, TEXT("%f ___ %f"), CursorPosition.X, CursorPosition.Y);
    //     AddControllerYawInput(-1 * RotationSpeed);
    // }
    // if (CursorPosition.X * -1 < CloseToEdgesValue)
    //{
    //      UE_LOG(LogTemp, Display, TEXT("%f ___ %f"), CursorPosition.X, CursorPosition.Y);
    //     AddControllerYawInput(1 * RotationSpeed);
    // }
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
    PlayerInputComponent->BindAxis("RotateCamera", this, &AMyCharacter::RotateCamera);
    PlayerInputComponent->BindAction("ZoomCamera", IE_Pressed, this, &AMyCharacter::ZoomCamera);
    PlayerInputComponent->BindAction("UnZoomCamera", IE_Pressed, this, &AMyCharacter::UnZoomCamera);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UMyWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UMyWeaponComponent::StopFire);
    //  PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, WeaponComponent, &UMyWeaponComponent::ChangeWeapon);
    PlayerInputComponent->BindAction("EquipSeccondaryWeapon", IE_Pressed, WeaponComponent, &UMyWeaponComponent::SwapToSeccondaryWeapon);
    PlayerInputComponent->BindAction("EquipMainWeapon", IE_Pressed, WeaponComponent, &UMyWeaponComponent::SwapToMainWeapon);
    PlayerInputComponent->BindAxis("LookAround", this, &AMyCharacter::LookAround);
}

int32 AMyCharacter::GetMuzzle()
{

    return WeaponComponent->GetCurrentWeaponIndex();
}
