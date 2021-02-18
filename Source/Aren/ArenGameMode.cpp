// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenGameMode.h"
#include "ArenPlayerController.h"
#include "ArenCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArenGameMode::AArenGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AArenPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}


/*
	Have a night and day cycle
	Have a specific time when enemies spawn

*/