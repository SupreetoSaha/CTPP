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
	
private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* _thisMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;

	int32 TriIndexCounter;

public:
	// Sets default values for this actor's properties
	AMeshWork();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DevelopmentalDriver();
	int32 GenerateTri(const TArray<FVector>& vertices,int32 triIndex = 0,bool invertedUV = false);
	int32 GenerateQuad(const TArray<FVector>& vertices,int32 triIndex0);
	int32 GenerateCube(const TArray<FVector>& vertices,int32 triIndex0);
};
