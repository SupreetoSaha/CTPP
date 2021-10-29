// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MeshWork.generated.h"

UCLASS()
class CTPP3_API AMeshWork : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeshWork();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * \brief for developmental and debugging purposes
	*/
	void developmentalDriver();

	/**
	 * \brief Public method for triangle mesh generation
	 * param vertices Array of vectors with the 3 vertices of the triangle to generate or replace
	 * param triIndex First index of the triangle to generete or replace
	 * param invertedUV Specifies if the applied UV should be inverted
	 * \return First index of generated triangle
	*/
	int32 generateTri(const TArray<FVector>& vertices,int32 triIndex = 0,bool invertedUV = false);

	/**
	 * \brief Public method for quadrilateral mesh generation
	 * param vertices Array of vectors with the 4 vertices of the quadrilateral to generate or replace
	 * param triIndex First index of the quadrilateral to generete or replace
	 * \return First index of generated quadrilateral
	*/
	int32 generateQuad(const TArray<FVector>& vertices,int32 triIndex0);

	/**
	 * \brief Public method for cube mesh generation
	 * param vertices Array of vectors with the 8 vertices of the cube to generate or replace
	 * param triIndex First index of the cube to generete or replace
	 * \return First index of generated cube
	*/
	int32 generateCube(const TArray<FVector>& vertices,int32 triIndex0);

private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* _thisMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;

	int32 TriIndexCounter;

};
