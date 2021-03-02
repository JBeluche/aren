// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Pawns/MainPlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Landscape.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMainPlayerPawn::AMainPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->SetupAttachment(RootComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AMainPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAround();

}

// Called to bind functionality to input
void AMainPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainPlayerPawn::MoveAround()
{
	
}
