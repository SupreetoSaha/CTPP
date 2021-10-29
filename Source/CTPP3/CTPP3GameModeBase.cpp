// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTPP3GameModeBase.h"

//

#include "UObject/ConstructorHelpers.h"
#include "ControlPanel.h"

ACTPP3GameModeBase::ACTPP3GameModeBase() {
	//PlayerControllerClass = Blueprint'/Game/Controller/Mouse_PlayerController.Mouse_PlayerController';
	HUDClass = AControlPanel::StaticClass();
}
