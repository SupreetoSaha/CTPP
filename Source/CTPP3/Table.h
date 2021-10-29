// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshWork.h"
#include "Chair.h"
#include "Table.generated.h"

/**
 * 
 */
UCLASS()
class CTPP3_API ATable : public AMeshWork
{
	GENERATED_BODY()

public:
	ATable();

	/**
	 * \brief Public method for furniture - table chair set - generation
	 * param corners Array of vectors with the 4 vertices of the table to generate or replace
	 * param tableHeight Height of the table to generete or replace
	 * param tableThickness Thickness of the table to generete or replace
	*/
	void generateFurniture(const TArray<FVector>& corners,const float& tableHeight,const float& tableThickness);

	/**
	 * \brief Public method for furniture - table chair set - generation
	 * param position Center (2D-vector) of the table to generate or replace
	 * param halfSize Half of the edge of the square table to generete or replace
	 * param tableHeight Height of the table to generete or replace
	 * param tableThickness Thickness of the table to generete or replace
	*/
	void generateFurniture(const FVector2D& position,const float& halfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners);

	/**
	 * \brief Public method for furniture - table chair set - generation
	 * param position Center (3D-vector) of the table to generate or replace
	 * param halfSize Half of the edge of the square table to generete or replace
	 * param tableHeight Height of the table to generete or replace
	 * param tableThickness Thickness of the table to generete or replace
	*/
	void generateFurniture(const FVector& position,const float& halfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners);

	/**
	 * \brief Public method for furniture - table chair set - resize or relocaion
	 * param cornerIndex Index of the table's corner to change
	 * param cornerPosition2D Old position of the table's corner to change
	 * param tableHeight Height of the table
	 * param corners Array for the new corners of the table
	*/
	void alterFurniture(const int8& cornerIndex,const FVector2D& cornerPosition2D,TArray<FVector2D>& corners);

	/**
	 * \brief Public method to query if point lies withen the 3D space
	 * param point Location of the point in question
	 * \return Whether or not the point lies withen the 3D space
	*/
	bool isPointInside(const FVector2D& point);

	/**
	 * \brief Public method for removing all chairs from furniture - table chair set
	*/
	void removeChairs();

private:
	float _tableHeight;
	float _tableThickness;
	float _edgeFrontLength;
	float _edgeFlankLength;
	FVector _centerPosition;
	TArray<FVector> _corners;
	TArray<AChair*> _chairList;

	/**
	 * \brief Private method to generate table
	 * param triIndex0 First index of table mesh
	 * \return Whether or not the point lies withen the 3D space
	*/
	int32 _generateTable(int32 triIndex0);

	/**
	 * \brief Private method for for furniture mesh generation
	*/
	void _generateFurniture();

	/**
	 * \brief Private method to update table corner
	 * param selfPosition Location of oneself (corner)
	 * param oldNeighbour Old location of neighbouring corner
	 * param newNeighbour New location of neighbouring corner
	*/
	void _updateNeighbour(FVector& selfPosition,const FVector& oldNeighbour,const FVector& newNeighbour);

	/**
	 * \brief Private method to calculate area of triangle
	 * param point1 Triangle vertex 1
	 * param point1 Triangle vertex 2
	 * param point1 Triangle vertex 3
	 * \return Area of triangle
	*/
	float _area(const FVector2D& point1,const FVector2D& point2,const FVector2D& point3);

	/**
	 * \brief Private method to calculate area of table top
	 * \return Area of table top
	*/
	float _area();

};
