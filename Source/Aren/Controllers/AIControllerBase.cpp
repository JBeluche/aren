// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Controllers/AIControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AAIControllerBase::AAIControllerBase()
{

}

void AAIControllerBase::BeginPlay()
{
    ArenCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);


    
    Super::BeginPlay();
}

void AAIControllerBase::Tick(float DeltaTime)
{
    //UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, ArenCharacter->GetActorLocation());
}


