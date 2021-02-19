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
	float TimeOfDay;
	float DayCycleSpeed;

	
};



