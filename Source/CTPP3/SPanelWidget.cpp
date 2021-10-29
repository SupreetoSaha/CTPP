// Fill out your copyright notice in the Description page of Project Settings.


#include "SPanelWidget.h"

#define LOCTEXT_NAMESPACE "Panel"

void SPanelWidget::Construct(const FArguments& InArgs) {
	const FText TitleText = LOCTEXT("ProjectTitle","Chair Table Practice Problem");
	const FMargin ContentPadding = FMargin(500.f,300.f);
	ChildSlot [
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill) [
				SNew(SImage)
					.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding) [
				SNew(SVerticalBox)
					+SVerticalBox::Slot() [
						SNew(STextBlock)
							.Text(TitleText)
					]
			]
	];
}

#undef LOCTEXT_NAMESPACE
