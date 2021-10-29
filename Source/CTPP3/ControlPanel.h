// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ControlPanel.generated.h"

/**
 * 
 */
UCLASS()
class CTPP3_API AControlPanel : public AHUD
{
	GENERATED_BODY()
	
protected:

	TSharedPtr<class SPanelWidget> PanelWidget;
	TSharedPtr<class SWidget> PanelContainer;

	virtual void BeginPlay() override;

};
