// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor2::AMyActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_actionState = EActionState::NONE;
	_worldMouseLocation = FVector(0);
	_worldMouseDirection = FVector(0);
	_myLocation = FVector(0);
	_mySolution = FVector(0);

	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = Camera;

	_worldMouseLocation = FVector(0);
	_worldMouseDirection = FVector(0);

	_inputRotation = FRotator(0);
	_maxRotationRate = 10;
	_rotationSpeed = 0.5;
	_rotationDeceleration = 0.1;

	_inputTranslation = FVector(0);
	_maxTranslationRate = 100;
	_translationDeceleration = 0.1;
}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();

	_bindToInput();
	_setPlayerController();
	_centerFurniture();
}

// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_locomotion(DeltaTime);
	//_screenPrint();
}

void AMyActor2::_setPlayerController() {
	UE_LOG(LogTemp,Display,TEXT("\t_setPlayerController\t"));

	_playerController = GetWorld()->GetFirstPlayerController();
	_playerController->bShowMouseCursor = true;
	_playerController->bEnableClickEvents = true;
	_playerController->bEnableMouseOverEvents = true;
	FInputModeGameOnly InputModeData; 
	InputModeData.SetConsumeCaptureMouseDown(false);
	_playerController->SetInputMode(InputModeData);

	_playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AMyActor2::_bindToInput() {
	UE_LOG(LogTemp,Display,TEXT("\t_bindToInput\t"));

	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if(InputComponent) {
		InputComponent->BindAction("MouseClick",IE_Pressed,this,&AMyActor2::_action_MouseClick_Pressed);
		InputComponent->BindAction("MouseClick",IE_Released,this,&AMyActor2::_action_MouseClick_Released);
		InputComponent->BindAction("Delete",IE_Pressed,this,&AMyActor2::_action_Delete);
		InputComponent->BindAxis("MouseMove",this,&AMyActor2::_axis_MouseMove);
		InputComponent->BindAxis("Turn",this,&AMyActor2::_axis_Turn);
		InputComponent->BindAxis("Pitch",this,&AMyActor2::_axis_Pitch);
		InputComponent->BindAxis("Horizontal",this,&AMyActor2::_axis_Horizontal);
		InputComponent->BindAxis("Vertical",this,&AMyActor2::_axis_Vertical);
		InputComponent->BindAxis("Straight",this,&AMyActor2::_axis_Straight);
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMyActor2::_action_MouseClick_Pressed() {
	UE_LOG(LogTemp,Display,TEXT("\tAction_MouseClick_Pressed\t"));

	_actionState = EActionState::CREATE;
	_furnitures.Reserve(_furnitures.Num());
	for(int32 i = _furnitures.Num()-1;0<=i;--i) {
		FFurniture& Furniture = _furnitures[i];
		for(int8 j = Furniture.Corners.Num()-1;0<=j;--j) {
			const FVector2D& Corner = Furniture.Corners[j];
			if(FVector2D::DistSquared(Corner,LineFloorIntersection(_myLocation,_worldMouseLocation,TableHeight))<TableThickness*TableThickness*3*3) {
				_alterationFurniture = &Furniture;
				_alterationCornerIndex = j;
				_actionState = EActionState::ALTER;
			}
		}
	}
}

void AMyActor2::_action_MouseClick_Released() {
	UE_LOG(LogTemp,Display,TEXT("\tAction_MouseClick_Released\t"));

	switch(_actionState) {
		case EActionState::CREATE:
			FFurniture Resultant;
			Resultant.Pointer = GetWorld()->SpawnActor<AActor_Table>(FVector(0),FRotator(0),FActorSpawnParameters());
			Resultant.Pointer->GenerateFurniture(_mySolution,TableSize/2,TableHeight,TableThickness,Resultant.Corners);
			_furnitures.Add(Resultant);
		break;
	}
	_actionState = EActionState::NONE;
}

void AMyActor2::_action_Delete() {
	UE_LOG(LogTemp,Display,TEXT("\t_action_Delete\t"));

	switch(_actionState) {
		case EActionState::NONE:
			_furnitures.Reserve(_furnitures.Num());
			for(int32 i = _furnitures.Num()-1;0<=i;--i) {
				FFurniture& Furniture = _furnitures[i];
				if(Furniture.Pointer->PointInside(LineFloorIntersection(_myLocation,_worldMouseLocation,TableHeight))) {
					Furniture.Pointer->RemoveChairs();
					Furniture.Pointer->Destroy();
					_furnitures.RemoveAt(i);
				}
			}
		break;
	}
}

void AMyActor2::_axis_MouseMove(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(111,10,FColor::Red,FString::Printf(TEXT("Axis_MouseMove:\n%f"),inputAxis));
	switch(_actionState) {
		case EActionState::ALTER:
			_alterationFurniture->Pointer->AlterFurniture(_alterationCornerIndex,LineFloorIntersection(_myLocation,_worldMouseLocation,TableHeight),_alterationFurniture->Corners);
		break;
	}
}

void AMyActor2::_axis_Turn(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(11,10,FColor::Turquoise,FString::Printf(TEXT("_axis_Turn:\n%f"),inputAxis));
	_inputTurn = FMath::Clamp(_inputTurn+inputAxis,-_maxRotationRate,_maxRotationRate);
}

void AMyActor2::_axis_Pitch(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(12,10,FColor::Turquoise,FString::Printf(TEXT("_axis_Pitch:\n%f"),inputAxis));
	_inputPitch = FMath::Clamp(_inputPitch+inputAxis,-_maxRotationRate,_maxRotationRate);
}

void AMyActor2::_axis_Straight(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(13,10,FColor::Turquoise,FString::Printf(TEXT("_axis_Straight:\n%f"),inputAxis));
	_inputTranslation.X = FMath::Clamp(_inputTranslation.X+inputAxis,-_maxTranslationRate,_maxTranslationRate);
}

void AMyActor2::_axis_Horizontal(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(14,10,FColor::Turquoise,FString::Printf(TEXT("_axis_Horizontal:\n%f"),inputAxis));
	_inputTranslation.Y = FMath::Clamp(_inputTranslation.Y+inputAxis,-_maxTranslationRate,_maxTranslationRate);
}

void AMyActor2::_axis_Vertical(float inputAxis) {
	//GEngine->AddOnScreenDebugMessage(15,10,FColor::Turquoise,FString::Printf(TEXT("_axis_Vertical:\n%f"),inputAxis));
	_inputTranslation.Z = FMath::Clamp(_inputTranslation.Z+inputAxis,-_maxTranslationRate,_maxTranslationRate);
}

void AMyActor2::_centerFurniture() {
	FFurniture CenterSet;
	FVector SpawnLocation_CenterTable(0.f);
	FRotator SpawnRotation_CenterTable(0.f);
	FActorSpawnParameters SpawnInfo_CenterTable;
	CenterSet.Pointer = GetWorld()->SpawnActor<AActor_Table>(SpawnLocation_CenterTable,SpawnRotation_CenterTable,SpawnInfo_CenterTable);
	TArray<FVector> Location{
		FVector(-100,-70,{}),
		FVector(-100,+70,{}),
		FVector(+100,+70,{}),
		FVector(+100,-70,{}),
	};
	CenterSet.Pointer->GenerateFurniture(Location,TableHeight,TableThickness);
	CenterSet.Corners = {
		FVector2D(-100,-70),
		FVector2D(-100,+70),
		FVector2D(+100,+70),
		FVector2D(+100,-70),
	};
	_furnitures.Add(CenterSet);
	
	// DrawDebugSphere(GetWorld(),FVector(CenterSet.Corners[0],TableHeight),15,12,FColor::Yellow,true,-1,0,1);
	// DrawDebugSphere(GetWorld(),FVector(CenterSet.Corners[1],TableHeight),15,12,FColor::Yellow,true,-1,0,1);
	// DrawDebugSphere(GetWorld(),FVector(CenterSet.Corners[2],TableHeight),15,12,FColor::Yellow,true,-1,0,1);
	// DrawDebugSphere(GetWorld(),FVector(CenterSet.Corners[3],TableHeight),15,12,FColor::Yellow,true,-1,0,1);
}

void AMyActor2::_locomotion(float deltaTime) {
	_playerController->DeprojectMousePositionToWorld(_worldMouseLocation,_worldMouseDirection);
	_myLocation = _playerPawn->GetActorLocation();
	_mySolution = FVector(LineFloorIntersection(_myLocation,_worldMouseLocation,FloorHeight),FloorHeight);

	AddActorWorldRotation(FQuat(FRotator(0,_inputTurn,0)),true);
	AddActorLocalRotation(FQuat(FRotator(_inputPitch,0,0)),true);
	_inputTurn *= _rotationDeceleration;
	_inputPitch *= _rotationDeceleration;

	AddActorLocalTransform(FTransform(FRotator(0),_inputTranslation*deltaTime*TranslationSpeed,FVector(0)),true);
	_inputTranslation *= _translationDeceleration;
}

void AMyActor2::_screenPrint() {
	if(GEngine) {
		_playerController->DeprojectMousePositionToWorld(_worldMouseLocation,_worldMouseDirection);
		GEngine->AddOnScreenDebugMessage(1,10,FColor::Magenta,FString::Printf(TEXT("_worldMouseLocation\nX: %f\nY: %f\nZ: %f"),_worldMouseLocation.X,_worldMouseLocation.Y,_worldMouseLocation.Z));
		DrawDebugBox(GetWorld(),_worldMouseLocation,FVector(0.2),FColor::Magenta,false,0,0,0.05);
		DrawDebugLine(GetWorld(),_worldMouseLocation,_worldMouseLocation+FVector(0,0,2),FColor::Magenta,false,0,0,0.05);
		GEngine->AddOnScreenDebugMessage(2,10,FColor::Magenta,FString::Printf(TEXT("_worldMouseDirection\nX: %f\nY: %f\nZ: %f"),_worldMouseDirection.X,_worldMouseDirection.Y,_worldMouseDirection.Z));
		GEngine->AddOnScreenDebugMessage(3,10,FColor::Purple,FString::Printf(TEXT("_myLocation\nX: %f\nY: %f\nZ: %f"),_myLocation.X,_myLocation.Y,_myLocation.Z));
		GEngine->AddOnScreenDebugMessage(4,10,FColor::Purple,FString::Printf(TEXT("Distance:\n%f"),FVector::Dist(_myLocation,_worldMouseLocation)));
		GEngine->AddOnScreenDebugMessage(5,10,FColor::Green,FString::Printf(TEXT("_mySolution\nX: %f\nY: %f\nZ: %f"),_mySolution.X,_mySolution.Y,_mySolution.Z));
	}
}

FVector2D AMyActor2::LineFloorIntersection(const FVector& point1,const FVector& point2,const float& floorHeight) {
	float dZ = point2.Z-point1.Z;
	FVector2D Resultant(0);
	if(dZ) {
		Resultant.X = point1.X+(floorHeight-point1.Z)*(point2.X-point1.X)/dZ;
		Resultant.Y = point1.Y+(floorHeight-point1.Z)*(point2.Y-point1.Y)/dZ;
	}
	return Resultant;
}
