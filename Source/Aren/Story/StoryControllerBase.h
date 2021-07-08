// Copyright CreatingMountains

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryControllerBase.generated.h"


class UDialogWidget;
class AArenPlayerController;


UCLASS()
class AREN_API AStoryControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoryControllerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

//--------------------
//	Variables
//--------------------

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
	TArray<APawn*> PlayersInStory;

	AArenPlayerController* PlayerController;
	UDialogWidget* DialogWidget;

	bool bPlayerControlsFrozen;
	bool bTimeStoped;
	FTimerHandle DialogTimeHandle;
	FTimerDelegate DialogTimerDelegate;

//--------------------
//	Functions
//--------------------

	UFUNCTION(BlueprintCallable)
	void DisplayDialog(FString DialogText, float TimeOnScreen);

	UFUNCTION(BlueprintCallable)
	void MoveCharacterTo(AActor* CharacterToMove, FVector Location);

	UFUNCTION(BlueprintCallable)
	void SetStopTime(bool bStopTime);

	UFUNCTION(BlueprintCallable)
	void SetFreezePlayerControls(bool bFreezePlayer);

	/*UFUNCTION(BlueprintCallable)
	APawn* GetCharacterFromArray(int32  ArrayNumber);*/

	UFUNCTION(BlueprintCallable)
	bool PlayAnimationOnCharacter(AActor* Actor, UAnimMontage*  MontageToPlay, bool bIsLooping);

	void RemoveDialog();



};
