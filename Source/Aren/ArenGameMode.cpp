// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenGameMode.h"
#include "ArenPlayerController.h"
#include "ArenCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

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

void AArenGameMode::BeginPlay()
{
	//TimeOfDay
	SecondsPerDay = float(MinutesPerDay) * 60.0f;
	SetTimeTo(6, 0);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AArenGameMode::MoveTime, 1.0f, true);

	Super::BeginPlay();

}

void AArenGameMode::SetTimeTo(int8 Hours, int8 Minutes)
{
/*	int TotalMinutes = (Hours * 60) + Minutes;
	SecondsPerDay
	ElapsedSeconds = NewTime;*/
}

void AArenGameMode::MoveTime()
{
	if(ElapsedSeconds >= SecondsPerDay)
	{
		ElapsedSeconds = 0.0f;
	}
	else
	{
		ElapsedSeconds = ElapsedSeconds + 1.0f;
	}	

	//Convert real seconds to world time
	float PercentPerSecond = ElapsedSeconds * 24.0f / SecondsPerDay;
	float MinutesToShow = PercentPerSecond * 60.0f / 1.0f;
	//Calculate time to show
	GameMinutes = int32(MinutesToShow) % 60;
	GameHours = int32(MinutesToShow) / 60;
}