// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveWidget.h"
#include "Components//Button.h"

void UMySaveWidget::NativeOnInitialized()
{
//	Super:NativeOnInitialized();

	if (SaveButton)
        {
        SaveButton->OnClicked.AddDynamic(this,&UMySaveWidget::SaveProgress);
        }
    }

void UMySaveWidget::SaveProgress()
{
}
