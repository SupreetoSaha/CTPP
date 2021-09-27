// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "Engine.h"

// Sets default values
AMyActor1::AMyActor1() : TriIndexCounter(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_thisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = _thisMesh;
	_thisMesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(APlayerController::IsInputKeyDown()) {
		UE_LOG(LogTemp,Display,TEXT("\tA\t"));
	}*/
}

void AMyActor1::PostActorCreated() {
	Super::PostActorCreated();
	//DevelopmentalDriver();
}

void AMyActor1::PostLoad() {
	Super::PostLoad();
	//DevelopmentalDriver();
}

int32 AMyActor1::GenerateTri(const TArray<FVector>& Vertices,int32 TriIndex,bool InvertedUV) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateTri\t"));
	UE_LOG(LogTemp,Display,TEXT("\tCalled with TriIndex:%d\t"),TriIndex);
	if(Vertices.Num()<3) {
		return 0;
	}
	if(!TriIndex) {
		TriIndex = ++TriIndexCounter;
	}

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector> normals;
	/*normals.Add(FVector(-1,0,0));
	normals.Add(FVector(-1,0,0));
	normals.Add(FVector(-1,0,0));*/

	float UvComponent1 = FVector::Dist(Vertices[0],Vertices[1])/50;
	float UvComponent2 = FVector::Dist(Vertices[0],Vertices[2])/50;
	TArray<FVector2D> UV;
	if(InvertedUV) {
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

	_thisMesh->CreateMeshSection_LinearColor(TriIndex,Vertices,Triangles,normals,UV,vertexColors,tangents,true);
	UE_LOG(LogTemp,Display,TEXT("\tReturning with TriIndex:%d\t"),TriIndex);
	return TriIndex;
}

int32 AMyActor1::GenerateQuad(const TArray<FVector>& Vertices,int32 TriIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateQuad\t"));
	if(Vertices.Num()<4) {
		return 0;
	}
	int32 TriIndex = TriIndex0 = GenerateTri({Vertices[0],Vertices[1],Vertices[3]},TriIndex0);
	if(TriIndex0) {
		TriIndex = GenerateTri({Vertices[2],Vertices[3],Vertices[1]},TriIndex0+1,true);
	}
	return TriIndex?TriIndex0:0;
}

int32 AMyActor1::GenerateCube(const TArray<FVector>& Vertices,int32 TriIndex0) {
	UE_LOG(LogTemp,Display,TEXT("\tGenerateCube\t"));
	if(Vertices.Num()<8) {
		return 0;
	}
	int32 TriIndex = TriIndex0 = GenerateQuad({Vertices[0],Vertices[1],Vertices[2],Vertices[3]},TriIndex0);
	if(TriIndex) {
		TriIndex = GenerateQuad({Vertices[4],Vertices[7],Vertices[6],Vertices[5]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = GenerateQuad({Vertices[0],Vertices[4],Vertices[5],Vertices[1]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = GenerateQuad({Vertices[2],Vertices[6],Vertices[7],Vertices[3]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = GenerateQuad({Vertices[0],Vertices[3],Vertices[7],Vertices[4]},TriIndex+2);
	}
	if(TriIndex) {
		TriIndex = GenerateQuad({Vertices[2],Vertices[1],Vertices[5],Vertices[6]},TriIndex+2);
	}
	return TriIndex?TriIndex0:0;
}

void AMyActor1::DevelopmentalDriver() {

	TArray<FVector> Vertices1{
		FVector(0,0,0),
		FVector(0,0,200),
		FVector(0,200,0),
	};
	GenerateTri(Vertices1);

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
	CenterTable->GenerateFurniture(Location_CenterTable);*/
}
