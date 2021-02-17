// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Actors/CampBase.h"

// Sets default values
ACampBase::ACampBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACampBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACampBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

