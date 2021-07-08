// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArenPlayerController.generated.h"

//Classes
class UUserWidget;
class AArenCharacter;
class ACampPawn;
class AMainPlayerPawn;
class ACharacterBase;


//Enums 
 UENUM(BlueprintType)
 enum class ECurrentPawn : uint8 
 {
      ARENCHARACTER UMETA(DisplayName = "Aren Character"),
      CAMP UMETA(DisplayName = "Camp"),
      DIALOG UMETA(DisplayName = "Dialog")
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

	UUserWidget* GetDialogWidget();


protected:

	virtual void BeginPlay() override;
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	//Varaibles C++
	TSubclassOf<class UUserWidget> CharacterControlClass;
	TSubclassOf<class UUserWidget> CampControlClass;
	TSubclassOf<class UUserWidget> DialogWidget;
	UUserWidget* Controls;
	AActor* MyOwner;
	
	AArenCharacter* ControlledCharater;

	//Varialbes Blueprint
	ACampPawn* CampPawn;
	AMainPlayerPawn* MainPlayerPawn;
	ACharacterBase* SelectedCharacter;


	FVector2D PreviousTouchLocation;
	FVector2D NewTouchLocation;
	bool bFingerReleased;
	bool bIsFingerTouching;
	float FingerTouchDuration;
	float LastFingerTouchDuration;
	FHitResult LastTouchHitResults;

	
	//Functions
	void SetOwner();

};