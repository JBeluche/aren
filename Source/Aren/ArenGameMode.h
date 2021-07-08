// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArenGameMode.generated.h"

class ASpawnArea;
class ACharacterBase;
class AArenGameStateBase;
class AStoryControllerBase;

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
	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	int MinutesPerDay;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ACharacterBase>> CharactersToSpawn;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AStoryControllerBase>> StoriesList;



	//Variables
	float SecondsPerDay = 0.0f;
	float ElapsedSeconds = 0.0f;
	int32 EnnemieCount;
	int GameMinutes;
	int GameHours;
	FTimerHandle TimerHandle;
	TArray<ASpawnArea*> SpawnAreaList;
	bool bHasSpawnedTonight; 
	

	//Functions
	void MoveTime();
	void SetTimeTo(int8 Hours, int8 minutes);
	FVector GetRandomSpawnLocation();
	void SpawnEnemies();

	AArenGameStateBase* GameState;

};



