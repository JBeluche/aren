// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Actors/BuildingBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	RootComponent = StaticMesh;

}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();

	OnInputTouchBegin.AddDynamic(this, &ABuildingBase::OnTouchBegin);

	
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBase::OnTouchBegin(ETouchIndex::Type FingerIndex, AActor* TouchedActor)
{
	UE_LOG(LogTemp, Error, TEXT("Shit got real sad"));
}