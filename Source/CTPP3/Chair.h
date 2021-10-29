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

	/**
	 * \brief Public method for chair mesh generation
	 * param position Center of the chair to generate
	 * param chairSize Size of the edge of the square chair to generate
	 * param chairHeight Height of the chair to generate
	 * param chairThickness Thickness of the chair to generate
	 * param triIndex0 First index of chair mesh
	 * \return First index of chair mesh
	*/
	int32 generateChair(const FVector& position,float chairSize,const float& chairHeight = 50,const float& chairThickness = 2,int32 triIndex0 = 0);

};
