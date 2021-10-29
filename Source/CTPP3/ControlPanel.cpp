// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPanel.h"
#include "SPanelWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AControlPanel::BeginPlay() {
	Super::BeginPlay();

	if(GEngine&&GEngine->GameViewport) {
		PanelWidget = SNew(SPanelWidget).OwningPanel(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(PanelContainer,SWeakWidget).PossiblyNullContent(PanelWidget.ToSharedRef()));
	}
}
