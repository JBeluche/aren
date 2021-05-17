// Copyright CreatingMountains


#include "Aren/Pawns/BoatPawn.h"

// Sets default values
ABoatPawn::ABoatPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

