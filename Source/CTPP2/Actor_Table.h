// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor1.h"
#include "Actor_Chair.h"
#include "Actor_Table.generated.h"

/**
 * 
 */
UCLASS()
class CTPP2_API AActor_Table : public AMyActor1
{
	GENERATED_BODY()
	
private:
	float _tableHeight;
	float _tableThickness;
	float _edgeFrontLength;
	float _edgeFlankLength;
	FVector _centerPosition;
	TArray<FVector> _corners;
	TArray<AActor_Chair*> _chairList;

	int32 _generateTable(int32 triIndex0);
	void _generateFurniture();
	void _updateNeighbour(FVector& selfPosition,const FVector& oldNeighbour,const FVector& newNeighbour);
	float _area(const FVector2D& point1,const FVector2D& point2,const FVector2D& point3);
	float _area();

public:
	AActor_Table();
	void GenerateFurniture(const TArray<FVector>& corners,const float& tableHeight,const float& tableThickness);
	void GenerateFurniture(const FVector2D& position,const float& halfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners);
	void GenerateFurniture(const FVector& position,const float& halfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners);
	void AlterFurniture(const int8& cornerIndex,const FVector2D& cornerPosition2D,TArray<FVector2D>& corners);
	bool PointInside(const FVector2D& point);
	void RemoveChairs();
};
