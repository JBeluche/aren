// Copyright CreatingMountains

#include "Aren/Story/StoryControllerBase.h"
#include "Aren/Story/DialogWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/ArenPlayerController.h"
#include "Aren/Actors/CharacterBase.h"

// Sets default values
AStoryControllerBase::AStoryControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStoryControllerBase::BeginPlay()
{
	Super::BeginPlay();
	//Get player controller
	PlayerController = Cast<AArenPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(!PlayerController){UE_LOG(LogTemp, Error, TEXT("No player controller"));return;}

	//Apprentently i need make vaiables. Passing directly crashes.


}
void AStoryControllerBase::DisplayDialog(FString DialogText, float TimeOnScreen)
{
	//Get controls from player controller, Controls is a user widget
	DialogWidget = Cast<UDialogWidget>(PlayerController->GetDialogWidget());
	if(!DialogWidget){ UE_LOG(LogTemp, Error, TEXT("Cast to dialog widget failed"));return;}

	SetFreezePlayerControls(true);

	//SetText
	DialogWidget->AddToViewport();
	DialogWidget->SetData(FText::FromString(DialogText));
	
	//Start timer
    UE_LOG(LogTemp, Error, TEXT("Setting timer that will remove text"));

	GetWorldTimerManager().SetTimer(DialogTimeHandle, this, &AStoryControllerBase::RemoveDialog, TimeOnScreen, false, TimeOnScreen);
	

	

}
void AStoryControllerBase::MoveCharacterTo(AActor* CharacterToMove, FVector Location)
{
}
void AStoryControllerBase::SetStopTime(bool bStopTime)
{
}
void AStoryControllerBase::SetFreezePlayerControls(bool bFreezePlayer)
{
	if(bFreezePlayer)
	{
		PlayerController->SwitchPawn(PlayerController->ECurrentPawn::DIALOG);
	}
	else{
		PlayerController->SwitchPawn(PlayerController->ECurrentPawn::ARENCHARACTER);
	}
}

void AStoryControllerBase::RemoveDialog()
{
	DialogWidget->SetData(FText::FromString(""));
	SetFreezePlayerControls(false);

}
/*
APawn* AStoryControllerBase::GetCharacterFromArray(int32  ArrayNumber)
{
	//Find character in level
    APawn* ActorFound = nullptr; 

    /*for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator) 
    { 
		if((PlayersInStory[ArrayNumber] != nullptr))
		{
  			if (PlayersInStory[ArrayNumber] = Cast<APawn>(*Iterator)); 
			{ 
				return ActorFound; 
			} 
		}
      
    } 
    return ActorFound; 
}*/

bool AStoryControllerBase::PlayAnimationOnCharacter(AActor* ActorToUse, UAnimMontage*  MontageToPlay, bool bIsLooping)
{
	ACharacterBase* Character = Cast<ACharacterBase>(ActorToUse);
	if(Character != nullptr){
		Character->PlayAnimationMontage(MontageToPlay, bIsLooping);

		return true;
	}
	return false;
}

