// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ArenCharacter.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Aren/Pawns/CampPawn.h"
#include "Aren/Pawns/CampPawn.h"
#include "EngineUtils.h"

AArenPlayerController::AArenPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCharacter(TEXT("/Game/Blueprints/Widgets/WBP_ControlsPlayer"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCamp(TEXT("/Game/Blueprints/Widgets/WBP_ControlsCamp"));
	
	CharacterControlClass = WBPControlsCharacter.Class;
	CampControlClass = WBPControlsCamp.Class;

	CampPawn = nullptr;
	
}

void AArenPlayerController::BeginPlay()
{
	//Selecting camp pawn
	for (TActorIterator<ACampPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CampPawn = *ActorItr;
	}
	//Selcting Aren Character Pawn
	ControlledCharater = Cast<AArenCharacter>(GetPawn());


}

void AArenPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	bool bIsFingerTouching;
	GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
	if(bIsFingerTouching)
	{
		AActor* MyOwner = Cast<AActor>(GetPawn());
		if(MyOwner)
		{
			float NewRotation = PreviousTouchLocation.X - NewTouchLocation.X;

			FRotator CurrentRotation = MyOwner->GetActorRotation();

			if(PreviousTouchLocation.X == 0.0f)
			{
				NewRotation = 0.0f;
			}

			UE_LOG(LogTemp, Error, TEXT("Fuck New rotation: %f, PreviousTouchLocation: %f, newTouchLocation: %f"), NewRotation, PreviousTouchLocation.X, NewTouchLocation.X);
		
			MyOwner->SetActorRotation(FRotator(CurrentRotation.Pitch, (CurrentRotation.Yaw + NewRotation), CurrentRotation.Roll));
		}
		PreviousTouchLocation = NewTouchLocation;
	}
	else
	{
		PreviousTouchLocation.X = 0.0f;
	}
}

void AArenPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AArenPlayerController::OnSetDestinationPressed);
	
	InputComponent->BindAction("SetDestination", IE_Released, this, &AArenPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AArenPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AArenPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AArenPlayerController::OnResetVR);

	Controls = CreateWidget<UUserWidget>( this, CharacterControlClass, FName("Character Controls"));
	Controls->AddToViewport();

}

void AArenPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AArenPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ControlledCharater)
		{
			if (ControlledCharater->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, ControlledCharater->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AArenPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AArenPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AArenPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AArenPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AArenPlayerController::SwitchPawn(ECurrentPawn NewPawn)
{
	CurrentPawnEnum = NewPawn;
	Controls->RemoveFromViewport();
	UnPossess();
	
	if(CurrentPawnEnum == ECurrentPawn::ARENCHARACTER)
	{
		Possess(ControlledCharater);
		Controls = CreateWidget<UUserWidget>( this, CharacterControlClass, FName("Character Controls"));
	}
	else if(CurrentPawnEnum == ECurrentPawn::CAMP)
	{
		
		Possess(CampPawn);
		Controls = CreateWidget<UUserWidget>( this, CampControlClass, FName("Camp Controls"));
	}

	Controls->AddToViewport();

}