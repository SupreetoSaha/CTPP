// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshWork.h"
#include "Chair.generated.h"

/**
 * 
 */
UCLASS()
class CTPP3_API AChair : public AMeshWork
{
	GENERATED_BODY()

public:
	int32 GenerateChair(const FVector& position,float chairSize,const float& chairHeight = 50,const float& chairThickness = 2,int32 triIndex0 = 0);
};
