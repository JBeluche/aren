// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArenGameMode.generated.h"

UCLASS(minimalapi)
class AArenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArenGameMode();

protected:
	virtual void BeginPlay() override;

private:

	//UPROPERTY
	UPROPERTY(EditAnywhere, Category = Time, meta = (AllowPrivateAccess = "true"))
	int MinutesPerDay;

	//Variables
	float SecondsPerDay = 0.0f;
	float ElapsedSeconds = 0.0f;
	int GameMinutes;
	int GameHours;
	FTimerHandle TimerHandle;
	void MoveTime();
	void SetTimeTo(int8 Hours, int8 minutes);

};



