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
	CurrentPawnEnum = ECurrentPawn::ARENCHARACTER;


}

void AArenPlayerController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	if(CurrentPawnEnum == ECurrentPawn::CAMP)
	{
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

				MyOwner->SetActorRotation(FRotator(CurrentRotation.Pitch, (CurrentRotation.Yaw + NewRotation), CurrentRotation.Roll));
			}
			PreviousTouchLocation = NewTouchLocation;
		}
		else
		{
			PreviousTouchLocation.X = 0.0f;
		}
	}
	else if(CurrentPawnEnum == ECurrentPawn::ARENCHARACTER)
	{
		GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
		if(bIsFingerTouching)
		{
			AActor* MyOwner = Cast<AActor>(GetPawn());
			if(MyOwner)
			{
				FVector CurrentLocation = MyOwner->GetActorLocation();
				float FloatToAddOnY = (PreviousTouchLocation.X - NewTouchLocation.X) * 5.0f;
				float FloatToAddOnX  = (PreviousTouchLocation.Y - NewTouchLocation.Y) * 5.0f;

				if(PreviousTouchLocation.X == 0.0f)
				{
					FloatToAddOnY  = 0.0f;
				}
				if(PreviousTouchLocation.Y == 0.0f)
				{
					FloatToAddOnX = 0.0f;
				}
				FVector NewLocation = MyOwner->GetActorLocation();
				//Up and Down swipe is X
				FloatToAddOnX = -1 * FloatToAddOnX;
				NewLocation.X = CurrentLocation.X + FloatToAddOnX;
				//Left and right swipe is Y
				NewLocation.Y = CurrentLocation.Y + FloatToAddOnY;

				MyOwner->SetActorLocation(NewLocation);
				//Look at how much the difference was to make a sort of speed when the finger is released
				PreviousTouchLocation = NewTouchLocation;

				//bFingerReleased = true;
			}
		}
		/*else if(bFingerReleased)
		{
			bFingerReleased = false;

		}*/
		else
		{
			PreviousTouchLocation.X = 0.0f;
			PreviousTouchLocation.Y = 0.0f;
		}
	}
}

void AArenPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	Controls = CreateWidget<UUserWidget>( this, CharacterControlClass, FName("Character Controls"));
	Controls->AddToViewport();

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