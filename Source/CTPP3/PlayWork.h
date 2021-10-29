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
	//CREATE,
	ALTER,
};

UCLASS()
class CTPP3_API APlayWork : public APawn
{
	GENERATED_BODY()

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

	UPROPERTY(EditAnywhere)
		bool bCenterFurniture = false;

	/**
	 * \brief Public method solving line-floor intersection
	 * param point1 Point-1 on line
	 * param point2 Point-2 on line
	 * param floorHeight Altitude of the floor
	 * \return Point of intersection (solution)
	*/
	FVector2D LineFloorIntersection(const FVector& point1,const FVector& point2,const float& floorHeight);

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
	FVector _myIntersection;

	FRotator _inputRotation;
	float _inputTurn;
	float _inputPitch;
	float _maxRotationRate;
	float _rotationSpeed;
	float _rotationDeceleration;

	FVector _inputTranslation;
	float _maxTranslationRate;
	float _translationDeceleration;

	/**
	 * \brief Private method for binding input to controller
	*/
	void _bindToInput();

	/**
	 * \brief Private method for player controller setup
	*/
	void _setPlayerController();

	/**
	 * \brief Private method for creating the initial central furniture
	*/
	void _centerFurniture();

	/**
	 * \brief Private method for player movement
	 * deltaTime Time difference between frames
	*/
	void _locomotion(float deltaTime);

	/**
	 * \brief Private method for displaying debug details
	*/
	void _screenPrint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * \brief Protected method for left mouse press
	*/
	void _action_MouseClick_Pressed();

	/**
	 * \brief Protected method for left mouse release
	*/
	void _action_MouseClick_Released();

	/**
	 * \brief Protected method for inserting furniture
	*/
    void _action_Insert();

	/**
	 * \brief Protected method for deleating furniture
	*/
	void _action_Delete();

	/**
	 * \brief Protected method for tracking mouse movement
	 * inputAxis Value from engine input
	*/
	void _axis_MouseMove(float inputAxis);

	/**
	 * \brief Protected method for tracking turn movement
	 * inputAxis Value from engine input
	*/
	void _axis_Turn(float inputAxis);

	/**
	 * \brief Protected method for tracking pitch movement
	 * inputAxis Value from engine input
	*/
	void _axis_Pitch(float inputAxis);

	/**
	 * \brief Protected method for tracking horizontal movement
	 * inputAxis Value from engine input
	*/
	void _axis_Horizontal(float inputAxis);

	/**
	 * \brief Protected method for tracking vertical movement
	 * inputAxis Value from engine input
	*/
	void _axis_Vertical(float inputAxis);

	/**
	 * \brief Protected method for tracking head-on movement
	 * inputAxis Value from engine input
	*/
	void _axis_Straight(float inputAxis);

};
