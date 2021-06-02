// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Actors/BuildingBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InitialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	RootComponent = InitialMesh;

}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

