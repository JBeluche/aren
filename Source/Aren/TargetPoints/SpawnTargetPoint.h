// Copyright CreatingMountains

#pragma once

#include "Aren/Actors/CharacterBase.h"
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnTargetPoint.generated.h"


UCLASS()
class AREN_API ASpawnTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawn parameters", meta = (AllowPrivateAccess = "true"))
	TArray<EFaction> AllowedFactionToSpawn;
}; 
