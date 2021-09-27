// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor1.h"
#include "Actor_Chair.generated.h"

/**
 * 
 */
UCLASS()
class CTPP2_API AActor_Chair : public AMyActor1
{
	GENERATED_BODY()

public:
	int32 GenerateChair(const FVector& position,float chairSize,const float& chairHeight = 50,const float& chairThickness = 2,int32 triIndex0 = 0);
};
