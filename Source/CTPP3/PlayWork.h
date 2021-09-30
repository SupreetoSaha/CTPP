// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Table.h"
#include "Camera/CameraComponent.h"
#include "PlayWork.generated.h"

USTRUCT()
struct FFurniture {
	GENERATED_USTRUCT_BODY()

	ATable* Pointer;
	TArray<FVector2D> Corners;
};

UENUM()
enum class EActionState {
	NONE,
	CREATE,
	ALTER,
};

UCLASS()
class CTPP3_API APlayWork : public APawn
{
	GENERATED_BODY()

private:
	APlayerController* _playerController;
	APawn* _playerPawn;

	TArray<FFurniture> _furnitures;
	EActionState _actionState;
	FFurniture* _alterationFurniture;
	int8 _alterationCornerIndex;

	FVector _worldMouseLocation;
	FVector _worldMouseDirection;
	FVector _myLocation;
	FVector _mySolution;

	FRotator _inputRotation;
	float _inputTurn;
	float _inputPitch;
	float _maxRotationRate;
	float _rotationSpeed;
	float _rotationDeceleration;

	FVector _inputTranslation;
	float _maxTranslationRate;
	float _translationDeceleration;

	void _bindToInput();
	void _setPlayerController();
	void _centerFurniture();
	void _locomotion(float);
	void _screenPrint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void _action_MouseClick_Pressed();
	void _action_MouseClick_Released();
	void _action_Delete();
	void _axis_MouseMove(float);
	void _axis_Turn(float);
	void _axis_Pitch(float);
	void _axis_Horizontal(float);
	void _axis_Vertical(float);
	void _axis_Straight(float);

public:
	// Sets default values for this pawn's properties
	APlayWork();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float TableHeight = 70;

	UPROPERTY(EditAnywhere)
		float TableSize = 120;

	UPROPERTY(EditAnywhere)
		float TableThickness = 5;

	UPROPERTY(EditAnywhere)
		float FloorHeight = 5;

	UPROPERTY(EditAnywhere)
		float TranslationSpeed = 200;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WorkerMeshComponent;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	FVector2D LineFloorIntersection(const FVector& point1,const FVector& point2,const float& floorHeight);
};
