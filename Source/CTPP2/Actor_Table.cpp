// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Table.h"

AActor_Table::AActor_Table() : _edgeFrontLength(0),_edgeFlankLength(0) {}

int32 AActor_Table::_generateTable(int32 _triIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\t_generateTable\t"));
	if(_corners.Num()<4) {
		return 0;
	}
	if(!_triIndex0) {
		++_triIndex0;
	}

	TArray<FVector> Vertices {
		FVector(_corners[0].X-_tableThickness*2,_corners[0].Y-_tableThickness*2,_tableHeight+_tableThickness),
		FVector(_corners[1].X-_tableThickness*2,_corners[1].Y+_tableThickness*2,_tableHeight+_tableThickness),
		FVector(_corners[2].X+_tableThickness*2,_corners[2].Y+_tableThickness*2,_tableHeight+_tableThickness),
		FVector(_corners[3].X+_tableThickness*2,_corners[3].Y-_tableThickness*2,_tableHeight+_tableThickness),
		FVector(_corners[0].X-_tableThickness*2,_corners[0].Y-_tableThickness*2,_tableHeight-_tableThickness),
		FVector(_corners[1].X-_tableThickness*2,_corners[1].Y+_tableThickness*2,_tableHeight-_tableThickness),
		FVector(_corners[2].X+_tableThickness*2,_corners[2].Y+_tableThickness*2,_tableHeight-_tableThickness),
		FVector(_corners[3].X+_tableThickness*2,_corners[3].Y-_tableThickness*2,_tableHeight-_tableThickness),
	};
	int32 TriIndex = _triIndex0 = GenerateCube(Vertices,_triIndex0);
	for(int8 i = 0;i<4;++i) {
		if(TriIndex) {
			Vertices = {
				FVector(_corners[i].X-_tableThickness,_corners[i].Y-_tableThickness,_tableHeight),
				FVector(_corners[i].X-_tableThickness,_corners[i].Y+_tableThickness,_tableHeight),
				FVector(_corners[i].X+_tableThickness,_corners[i].Y+_tableThickness,_tableHeight),
				FVector(_corners[i].X+_tableThickness,_corners[i].Y-_tableThickness,_tableHeight),
				FVector(_corners[i].X-_tableThickness,_corners[i].Y-_tableThickness,0),
				FVector(_corners[i].X-_tableThickness,_corners[i].Y+_tableThickness,0),
				FVector(_corners[i].X+_tableThickness,_corners[i].Y+_tableThickness,0),
				FVector(_corners[i].X+_tableThickness,_corners[i].Y-_tableThickness,0),
			};
			TriIndex = GenerateCube(Vertices,TriIndex+12);
		}
	}

	return TriIndex?_triIndex0:0;
}

void AActor_Table::_generateFurniture() {
	UE_LOG(LogTemp,Display,TEXT("\t_generateFurniture\t"));
	uint8 CornerCount = _corners.Num();
	if(CornerCount<4) {
		UE_LOG(LogTemp,Error,TEXT("\tRequest to _generateFurniture with %d corners, instead of 4.\t"),CornerCount);
		return;
	}

	_edgeFrontLength = FVector::Dist(_corners[0],_corners[1]);
	_edgeFlankLength = FVector::Dist(_corners[1],_corners[2]);
	_centerPosition = (_corners[0]+_corners[1]+_corners[2]+_corners[3])/4;

	RemoveChairs();
	int32 _triIndex0 = _generateTable(1);

	int32 ChairSize		{48};
	int32 ChairHeight	{90};
	int32 ChairGap		{15};
	int32 ChairSpace	{ChairSize+ChairGap};

	FActorSpawnParameters SpawnInfo_Chair;

	int32 EdgeCount {};
	float CenterDistance {};
	float EdgeDistance {};
	float EdgePosition {};

	EdgeCount = _edgeFlankLength/ChairSpace;
	CenterDistance = 1.f*_edgeFlankLength/EdgeCount;
	EdgeDistance = _edgeFrontLength/2.f;
	EdgePosition = -_edgeFlankLength/2.f+CenterDistance/2.f;
	for(int32 i{0};i<EdgeCount;++i) {
		AActor_Chair* ChairLeft = GetWorld()->SpawnActor<AActor_Chair>({_centerPosition.X+EdgePosition,_centerPosition.Y-EdgeDistance-ChairSize,0},{0,90,0},SpawnInfo_Chair);
		ChairLeft->GenerateChair(FVector(0),ChairSize,ChairHeight);
		_chairList.Add(ChairLeft);
		AActor_Chair* ChairRight = GetWorld()->SpawnActor<AActor_Chair>({_centerPosition.X+EdgePosition,_centerPosition.Y+EdgeDistance+ChairSize,0},{0,-90,0},SpawnInfo_Chair);
		ChairRight->GenerateChair(FVector(0),ChairSize,ChairHeight);
		_chairList.Add(ChairRight);
		EdgePosition += CenterDistance;
	}

	EdgeCount = _edgeFrontLength/ChairSpace;
	CenterDistance = 1.f*_edgeFrontLength/EdgeCount;
	EdgeDistance = _edgeFlankLength/2.f;
	EdgePosition = -_edgeFrontLength/2.f+CenterDistance/2.f;
	for(int32 i{0};i<EdgeCount;++i) {
		AActor_Chair* ChairBack = GetWorld()->SpawnActor<AActor_Chair>({_centerPosition.X-EdgeDistance-ChairSize,_centerPosition.Y+EdgePosition,0},{0,0,0},SpawnInfo_Chair);
		ChairBack->GenerateChair(FVector(0),ChairSize,ChairHeight);
		_chairList.Add(ChairBack);
		AActor_Chair* ChairFace = GetWorld()->SpawnActor<AActor_Chair>({_centerPosition.X+EdgeDistance+ChairSize,_centerPosition.Y+EdgePosition,0},{0,180,0},SpawnInfo_Chair);
		ChairFace->GenerateChair(FVector(0),ChairSize,ChairHeight);
		_chairList.Add(ChairFace);
		EdgePosition += CenterDistance;
	}

	UE_LOG(LogTemp,Display,TEXT("\tCenterPosition\t%f\t%f\t%f"),_centerPosition.X,_centerPosition.Y,_centerPosition.Z);	// this line	
}

void AActor_Table::_updateNeighbour(FVector& selfPosition,const FVector& oldNeighbour,const FVector& newNeighbour) {
	if(FMath::IsNearlyEqual(selfPosition.X,oldNeighbour.X)) {
		selfPosition.X = newNeighbour.X;
	}
	if(FMath::IsNearlyEqual(selfPosition.Y,oldNeighbour.Y)) {
		selfPosition.Y = newNeighbour.Y;
	}
}

float AActor_Table::_area(const FVector2D& point1,const FVector2D& point2,const FVector2D& point3) {
	float Area {(point1.X*(point2.Y-point3.Y)+point2.X*(point3.Y-point1.Y)+point3.X*(point1.Y-point2.Y))/2};
	return FMath::Abs(Area);
}

float AActor_Table::_area() {
	return _area(FVector2D(_corners[0]),FVector2D(_corners[1]),FVector2D(_corners[2]))
		+ _area(FVector2D(_corners[0]),FVector2D(_corners[3]),FVector2D(_corners[2]));
}

void AActor_Table::GenerateFurniture(const TArray<FVector>& corners,const float& tableHeight,const float& tableThickness) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateFurniture-1\t"));

	_corners = corners;
	_tableHeight = tableHeight;
	_tableThickness = tableThickness;

	_generateFurniture();
}

void AActor_Table::GenerateFurniture(const FVector2D& position,const float& halfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateFurniture-2\t"));

	_corners = {
		FVector(position+FVector2D(-halfSize,-halfSize),tableHeight),
		FVector(position+FVector2D(-halfSize,+halfSize),tableHeight),
		FVector(position+FVector2D(+halfSize,+halfSize),tableHeight),
		FVector(position+FVector2D(+halfSize,-halfSize),tableHeight),
	};
	_tableHeight = tableHeight;
	_tableThickness = tableThickness;
	resultantCorners = {
		FVector2D(position+FVector2D(-halfSize,-halfSize)),
		FVector2D(position+FVector2D(-halfSize,+halfSize)),
		FVector2D(position+FVector2D(+halfSize,+halfSize)),
		FVector2D(position+FVector2D(+halfSize,-halfSize)),
	};

	_generateFurniture();
}

void AActor_Table::GenerateFurniture(const FVector& Position,const float& HalfSize,const float& tableHeight,const float& tableThickness,TArray<FVector2D>& resultantCorners) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateFurniture-3\t"));

	_corners = {
		Position+FVector(-HalfSize,-HalfSize,tableHeight),
		Position+FVector(-HalfSize,+HalfSize,tableHeight),
		Position+FVector(+HalfSize,+HalfSize,tableHeight),
		Position+FVector(+HalfSize,-HalfSize,tableHeight),
	};
	_tableHeight = tableHeight;
	_tableThickness = tableThickness;
	resultantCorners = {
		FVector2D(Position)+FVector2D(-HalfSize,-HalfSize),
		FVector2D(Position)+FVector2D(-HalfSize,+HalfSize),
		FVector2D(Position)+FVector2D(+HalfSize,+HalfSize),
		FVector2D(Position)+FVector2D(+HalfSize,-HalfSize),
	};
	
	_generateFurniture();
}

void AActor_Table::AlterFurniture(const int8& cornerIndex,const FVector2D& cornerPosition2D,TArray<FVector2D>& corners) {
	UE_LOG(LogTemp,Display,TEXT("\tAlterFurniture\t"));

	FVector NewPosition = FVector(cornerPosition2D,_tableHeight);
	uint8 CornerCount = _corners.Num();
	_updateNeighbour(_corners[cornerIndex?cornerIndex-1:CornerCount-1],_corners[cornerIndex],NewPosition);
	_updateNeighbour(_corners[(cornerIndex+1)%CornerCount],_corners[cornerIndex],NewPosition);
	_corners[cornerIndex] = NewPosition;

	_generateFurniture();

	corners.Empty();
	for(const FVector& Vector:_corners) {
		corners.Emplace(FVector2D(Vector));
	}
}

bool AActor_Table::PointInside(const FVector2D& point) {
	UE_LOG(LogTemp,Display,TEXT("\tPointInside\t"));

	float PointArea {
		_area(point,FVector2D(_corners[0]),FVector2D(_corners[1])) +
		_area(point,FVector2D(_corners[1]),FVector2D(_corners[2])) +
		_area(point,FVector2D(_corners[2]),FVector2D(_corners[3])) +
		_area(point,FVector2D(_corners[3]),FVector2D(_corners[0]))
	};
	return PointArea<=_area();
}

void AActor_Table::RemoveChairs() {
	UE_LOG(LogTemp,Display,TEXT("\tRemoveChairs\t"));

	for(auto Chair:_chairList) {
		Chair->Destroy();
	}
	_chairList.Empty();
}
