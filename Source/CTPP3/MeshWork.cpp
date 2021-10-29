// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshWork.h"

// Sets default values
AMeshWork::AMeshWork() : TriIndexCounter(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_thisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = _thisMesh;
	_thisMesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void AMeshWork::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeshWork::PostActorCreated() {
	Super::PostActorCreated();
	// developmentalDriver();
}

void AMeshWork::PostLoad() {
	Super::PostLoad();
	// developmentalDriver();
}

// Called every frame
void AMeshWork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMeshWork::generateTri(const TArray<FVector>& vertices,int32 triIndex,bool invertedUV) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateTri\t"));
	UE_LOG(LogTemp,Display,TEXT("\tCalled with triIndex:%d\t"),triIndex);
	if(vertices.Num()<3) {
		return 0;
	}
	if(!triIndex) {
		triIndex = ++TriIndexCounter;
	}

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector> normals;
	/*normals.Add(FVector(-1,0,0));
	normals.Add(FVector(-1,0,0));
	normals.Add(FVector(-1,0,0));*/

	float UvComponent1 {FVector::Dist(vertices[0],vertices[1])/50};
	float UvComponent2 {FVector::Dist(vertices[0],vertices[2])/50};
	TArray<FVector2D> UV;
	if(invertedUV) {
		UV.Add(FVector2D(UvComponent1,UvComponent2));
		UV.Add(FVector2D(0,UvComponent2));
		UV.Add(FVector2D(UvComponent1,0));
	}
	else {
		UV.Add(FVector2D(0,0));
		UV.Add(FVector2D(UvComponent1,0));
		UV.Add(FVector2D(0,UvComponent2));
	}

	TArray<FProcMeshTangent> tangents;
	/*tangents.Add(FProcMeshTangent(0,1,0));
	tangents.Add(FProcMeshTangent(0,1,0));
	tangents.Add(FProcMeshTangent(0,1,0));*/

	TArray<FLinearColor> vertexColors;
	/*vertexColors.Add(FLinearColor(0.75,0.75,0.75,1.0));
	vertexColors.Add(FLinearColor(0.75,0.75,0.75,1.0));
	vertexColors.Add(FLinearColor(0.75,0.75,0.75,1.0));*/

	_thisMesh->CreateMeshSection_LinearColor(triIndex,vertices,Triangles,normals,UV,vertexColors,tangents,true);
	UE_LOG(LogTemp,Display,TEXT("\tReturning with TriIndex:%d\t"),triIndex);
	return triIndex;
}

int32 AMeshWork::generateQuad(const TArray<FVector>& vertices,int32 triIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateQuad\t"));
	if(vertices.Num()<4) {
		return 0;
	}
	int32 TriIndex = triIndex0 = generateTri({vertices[0],vertices[1],vertices[3]},triIndex0);
	if(triIndex0) {
		TriIndex = generateTri({vertices[2],vertices[3],vertices[1]},triIndex0+1,true);
	}
	return TriIndex?triIndex0:0;
}

int32 AMeshWork::generateCube(const TArray<FVector>& vertices,int32 triIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateCube\t"));
	if(vertices.Num()<8) {
		return 0;
	}
	int32 TriIndex = triIndex0 = generateQuad({vertices[0],vertices[1],vertices[2],vertices[3]},triIndex0);
	if(TriIndex) {
		TriIndex = generateQuad({vertices[4],vertices[7],vertices[6],vertices[5]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = generateQuad({vertices[0],vertices[4],vertices[5],vertices[1]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = generateQuad({vertices[2],vertices[6],vertices[7],vertices[3]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = generateQuad({vertices[0],vertices[3],vertices[7],vertices[4]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = generateQuad({vertices[2],vertices[1],vertices[5],vertices[6]},TriIndex+2);
	}
	return TriIndex?triIndex0:0;
}

void AMeshWork::developmentalDriver() {

	TArray<FVector> Vertices1{
		FVector(0,0,0),
		FVector(0,0,200),
		FVector(0,200,0),
	};
	generateTri(Vertices1);

	/*FVector SpawnLocation_CenterTable(0.f);
	FRotator SpawnRotation_CenterTable(0.f);
	FActorSpawnParameters SpawnInfo_CenterTable;
	AActor_Table* CenterTable = GetWorld()->SpawnActor<AActor_Table>(SpawnLocation_CenterTable,SpawnRotation_CenterTable,SpawnInfo_CenterTable);
	TArray<FVector> Location_CenterTable{
			FVector(-100,-70,{}),
			FVector(-100,+70,{}),
			FVector(+100,+70,{}),
			FVector(+100,-70,{}),
	};
	CenterTable->generateFurniture(Location_CenterTable);*/
}
