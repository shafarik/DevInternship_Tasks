// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEVINTERNSHIP_TASKS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
    AMyPlayerController();

	protected:
    virtual void BeginPlay()override;
	virtual void SetupInputComponent()override;

	private:
    void OnPauseGame();
        void OnMatchStateChanged(EMatchState State);
	
};
