// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Controls/CampControls.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/ArenPlayerController.h"

bool UCampControls::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;

	if (!ensure(CharacterView != nullptr)) return false;
    CharacterView->OnClicked.AddDynamic(this, &UCampControls::SwitchToCharacter);

    PlayerController = Cast<AArenPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    return true;
}

void UCampControls::SwitchToCharacter()
{
    PlayerController->SwitchPawn(PlayerController->ECurrentPawn::ARENCHARACTER);

}
