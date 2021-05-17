// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Aren/Actors/CharacterBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnArea.generated.h"

class USphereComponent;

UCLASS()
class AREN_API ASpawnArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnArea();
	
	float GetSphereComponentRadius();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SpawnArea;

	//Which faction can spawn	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawn parameters", meta = (AllowPrivateAccess = "true"))
	TArray<EFaction> AllowedFactionToSpawn;

	//If a boat can spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawn parameters", meta = (AllowPrivateAccess = "true"))
	bool bCanSpawnBoat;
};
