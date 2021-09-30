// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Chair.h"

int32 AActor_Chair::GenerateChair(const FVector& position,float chairSize,const float& chairHeight,const float& chairThickness,int32 triIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateChair\t"));
	if(!triIndex0) {
		++triIndex0;
	}

	if(1<chairSize) {
		chairSize /= 2;
	}
	else {
		return 0;
	}

	float HalfHeight = chairHeight/2;
	FVector2D PositionA(position.X-chairSize,position.Y-chairSize);
	FVector2D PositionB(position.X-chairSize,position.Y+chairSize);
	FVector2D PositionC(position.X+chairSize,position.Y+chairSize);
	FVector2D PositionD(position.X+chairSize,position.Y-chairSize);

	TArray<FVector> Vertices {
		FVector(PositionA.X-chairThickness,PositionA.Y-chairThickness,HalfHeight+chairThickness),
		FVector(PositionB.X-chairThickness,PositionB.Y+chairThickness,HalfHeight+chairThickness),
		FVector(PositionC.X+chairThickness,PositionC.Y+chairThickness,HalfHeight+chairThickness),
		FVector(PositionD.X+chairThickness,PositionD.Y-chairThickness,HalfHeight+chairThickness),
		FVector(PositionA.X-chairThickness,PositionA.Y-chairThickness,HalfHeight-chairThickness),
		FVector(PositionB.X-chairThickness,PositionB.Y+chairThickness,HalfHeight-chairThickness),
		FVector(PositionC.X+chairThickness,PositionC.Y+chairThickness,HalfHeight-chairThickness),
		FVector(PositionD.X+chairThickness,PositionD.Y-chairThickness,HalfHeight-chairThickness),
	};
	
	int32 TriIndex = triIndex0 = GenerateCube(Vertices,triIndex0);

	if(TriIndex) {
		Vertices = {
			FVector(PositionA,HalfHeight),
			FVector(PositionB,HalfHeight),
			FVector(PositionB,chairHeight),
			FVector(PositionA,chairHeight),
			FVector(PositionA.X+chairThickness,PositionA.Y,HalfHeight),
			FVector(PositionB.X+chairThickness,PositionB.Y,HalfHeight),
			FVector(PositionB.X+chairThickness,PositionB.Y,chairHeight),
			FVector(PositionA.X+chairThickness,PositionA.Y,chairHeight),
		};
		TriIndex = GenerateCube(Vertices,TriIndex+12);
	}

	if(TriIndex) {
		Vertices = {
			FVector(PositionA,HalfHeight),
			FVector(PositionD,HalfHeight),
			FVector(PositionD,0),
			FVector(PositionA,0),
			FVector(PositionA.X,PositionA.Y+chairThickness,HalfHeight),
			FVector(PositionD.X,PositionD.Y+chairThickness,HalfHeight),
			FVector(PositionD.X,PositionD.Y+chairThickness,0),
			FVector(PositionA.X,PositionA.Y+chairThickness,0),
		};
		TriIndex = GenerateCube(Vertices,TriIndex+12);
	}

	if(TriIndex) {
		Vertices = {
			FVector(PositionC,HalfHeight),
			FVector(PositionB,HalfHeight),
			FVector(PositionB,0),
			FVector(PositionC,0),
			FVector(PositionC.X,PositionC.Y-chairThickness,HalfHeight),
			FVector(PositionB.X,PositionB.Y-chairThickness,HalfHeight),
			FVector(PositionB.X,PositionB.Y-chairThickness,0),
			FVector(PositionC.X,PositionC.Y-chairThickness,0),
		};
		TriIndex = GenerateCube(Vertices,TriIndex+12);
	}

	return TriIndex?triIndex0:0;
}
