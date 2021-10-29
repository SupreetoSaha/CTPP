// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "ControlsWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CTPP3_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UUserWidget> ControlsWidgetClass;

private:

	UControlsWidget* ControlsWidget;

};
