// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenGameMode.h"
#include "ArenPlayerController.h"
#include "ArenCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/Actors/SpawnArea.h"
#include "Math/UnrealMathUtility.h"
#include "Aren/Pawns/MainPlayerPawn.h"

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
	EnnemieCount = 12;
	bHasSpawnedTonight = false;
}

void AArenGameMode::SetTimeTo(int8 Hours, int8 Minutes)
{
	/*	int TotalMinutes = (Hours * 60) + Minutes;
	SecondsPerDay
	ElapsedSeconds = NewTime;*/
}

void AArenGameMode::MoveTime()
{
	if (ElapsedSeconds >= SecondsPerDay)
	{
		ElapsedSeconds = 0.0f;
	}
	else
	{
		ElapsedSeconds = ElapsedSeconds + 1.0f;
	}

	//To Remove Or Change
	if (ElapsedSeconds >= 5 && bHasSpawnedTonight == false)
	{
		SpawnEnemies();
	}

	//Convert real seconds to world time
	float PercentPerSecond = ElapsedSeconds * 24.0f / SecondsPerDay;
	float MinutesToShow = PercentPerSecond * 60.0f / 1.0f;
	//Calculate time to show
	GameMinutes = int32(MinutesToShow) % 60;
	GameHours = int32(MinutesToShow) / 60;
}
void AArenGameMode::SpawnEnemies()
{
	for (int32 i = 0; i < EnnemieCount; i++)
	{
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

		UObject *SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_MainPlayerPawn")));

		UBlueprint *GeneratedBP = Cast<UBlueprint>(SpawnActor);
		if (!SpawnActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		UClass *SpawnClass = SpawnActor->StaticClass();
		if (SpawnClass == NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
			return;
		}

		UWorld *World = GetWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AMainPlayerPawn *CharacterBase = World->SpawnActor<AMainPlayerPawn>(GeneratedBP->GeneratedClass, GetRandomSpawnLocation(), Rotation, SpawnParams);
		CharacterBase->SpawnDefaultController();
	}

	bHasSpawnedTonight = true;
}

FVector AArenGameMode::GetRandomSpawnLocation()
{
	//Get all sphere circles
	for (TActorIterator<ASpawnArea> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SpawnAreaList.Push(*ActorItr);
	}
	//Select a random one between all of them
	int32 RandomSpawnNumber = FMath::RandRange(0, (SpawnAreaList.Num() - 1));

	UE_LOG(LogTemp, Error, TEXT("Selected array item is %s"), *SpawnAreaList[RandomSpawnNumber]->GetName());
	//Select a random location in spawn
	float Radius = SpawnAreaList[RandomSpawnNumber]->GetSphereComponentRadius();
	FVector SpawnAreaActorLocation = SpawnAreaList[RandomSpawnNumber]->GetActorLocation();

	FVector LocationToSpawn = FVector();
	LocationToSpawn.X = FMath::FRandRange((SpawnAreaActorLocation.X + Radius), (SpawnAreaActorLocation.X - Radius));
	LocationToSpawn.Y = FMath::FRandRange((SpawnAreaActorLocation.Y + Radius), (SpawnAreaActorLocation.Y - Radius));
	LocationToSpawn.Z = SpawnAreaActorLocation.Z;

	return LocationToSpawn;
}

