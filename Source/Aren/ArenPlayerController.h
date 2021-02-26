// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArenPlayerController.generated.h"

//Classes
class UUserWidget;
class AArenCharacter;
class ACampPawn;


//Enums 
 UENUM(BlueprintType)
 enum class ECurrentPawn : uint8 
 {
      ARENCHARACTER UMETA(DisplayName = "Aren Character"),
      CAMP UMETA(DisplayName = "Camp")
 };

UCLASS()
class AArenPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArenPlayerController();

	void SwitchPawn(ECurrentPawn NewPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECurrentPawn CurrentPawnEnum;

protected:

	virtual void BeginPlay() override;
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:

	//Varaibles C++
	TSubclassOf<class UUserWidget> CharacterControlClass;
	TSubclassOf<class UUserWidget> CampControlClass;
	UUserWidget* Controls;
	
	AArenCharacter* ControlledCharater;

	//Varialbes Blueprint
	ACampPawn* CampPawn;

	FVector2D PreviousTouchLocation;
	FVector2D NewTouchLocation;

	
	//Functions

};


