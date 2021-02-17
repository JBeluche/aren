// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Controls/MainCharacterControls.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/ArenPlayerController.h"

bool UMainCharacterControls::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;

	if (!ensure(CampView != nullptr)) return false;
    CampView->OnClicked.AddDynamic(this, &UMainCharacterControls::SwitchToCamp);

    PlayerController = Cast<AArenPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    return true;
}

void UMainCharacterControls::SwitchToCamp()
{
 
   PlayerController->SwitchPawn(PlayerController->ECurrentPawn::CAMP);
}
