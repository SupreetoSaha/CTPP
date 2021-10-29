// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SPanelWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SPanelWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AControlPanel>, OwningPanel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AControlPanel> OwningPanel;

	virtual bool SupportsKeyboardFocus() const override {return true;};

};
