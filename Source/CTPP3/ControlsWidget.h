// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ControlsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CTPP3_API UControlsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UControlsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	class UTextBlock* Text;
};
