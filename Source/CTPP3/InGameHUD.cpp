// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD() {}

void AInGameHUD::DrawHUD() {
	Super::DrawHUD();
}

void AInGameHUD::BeginPlay() {
	Super::BeginPlay();
	if(ControlsWidgetClass) {
		ControlsWidget = CreateWidget<UControlsWidget>(GetWorld(),ControlsWidgetClass);
		if(ControlsWidget) {
			ControlsWidget->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
