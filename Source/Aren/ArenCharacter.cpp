// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AArenCharacter::AArenCharacter()
{

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(RootComponent);

	

	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm*/


}

void AArenCharacter::BeginPlay()
{
	Super::BeginPlay();
		
	FVector CurrentActorLocation = GetActorLocation();
	FVector NewLocation = FVector();
	NewLocation.X = CurrentActorLocation.X;
	NewLocation.Y = CurrentActorLocation.Y;
	NewLocation.Z = CurrentActorLocation.Z + 5000.0f;
	TopDownCameraComponent->ApplyWorldOffset(NewLocation, false);

}

void AArenCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	//Get current camera view
}

