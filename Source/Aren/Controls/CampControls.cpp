// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Controls/CampControls.h"
#include "Aren/Controls/BuildingListItem.h"
#include "Aren/Actors/BuildingBase.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/ArenPlayerController.h"

void UCampControls::NativeConstruct()
{

    Super::NativeConstruct();

    if (!ensure(CharacterView != nullptr))
    {
        return;
    }
    CharacterView->OnClicked.AddDynamic(this, &UCampControls::SwitchToCharacter);

    if (!ensure(B_Build != nullptr))
    {
        return;
    }
    B_Build->OnClicked.AddDynamic(this, &UCampControls::OpenBuildMenu);

    PlayerController = Cast<AArenPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

void UCampControls::SwitchToCharacter()
{
    PlayerController->SwitchPawn(PlayerController->ECurrentPawn::ARENCHARACTER);
}

void UCampControls::OpenBuildMenu()
{
    TArray<AActor *> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingBase::StaticClass(), FoundActors);

    for (int i = 0; i < FoundActors.Num(); i++)
    {
        if (FoundActors[i] != nullptr && Cast<ABuildingBase>(FoundActors[i]))
        {
            ABuildingBase *Item = Cast<ABuildingBase>(FoundActors[i]);
            if (BuildingItemContainer)
            {
                if (BuildingBlueprint)
                {
                    UBuildingListItem *Widget = CreateWidget<UBuildingListItem>(this, BuildingBlueprint);
                    if (Widget)
                    {
                        BuildingItemContainer->AddChildToWrapBox(Widget);
                        if (Widget->TB_NameBuilding)
                        {
                            Widget->SetData(FText::FromString(Item->GetName()));
                        }
                    }
                }
            }
        }
    }
}
