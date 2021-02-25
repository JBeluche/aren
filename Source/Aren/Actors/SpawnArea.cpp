// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Actors/SpawnArea.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpawnArea::ASpawnArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnArea = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn Area"));

}

// Called when the game starts or when spawned
void ASpawnArea::BeginPlay()
{
	Super::BeginPlay();
	
}

float ASpawnArea::GetSphereComponentRadius()
{
	return SpawnArea->GetScaledSphereRadius();
}