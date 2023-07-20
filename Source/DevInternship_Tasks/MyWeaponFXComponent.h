// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyWeaponFXComponent.generated.h"

class UParticleSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVINTERNSHIP_TASKS_API UMyWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyWeaponFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UParticleSystem* MuzzleFX;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayImpactFX(const FHitResult& Hit );

		
};
