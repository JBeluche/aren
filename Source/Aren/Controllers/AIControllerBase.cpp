// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Controllers/AIControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Aren/Actors/CharacterBase.h"

AAIControllerBase::AAIControllerBase()
{
}

void AAIControllerBase::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehaviorTree != nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);

        //Get all player that are not of his faction
        GetBlackboardComponent()->SetValueAsObject(TEXT("AttackTarget"), GetClosestEnnemy());
    }
}

void AAIControllerBase::Tick(float DeltaTime)
{
}

ACharacterBase *AAIControllerBase::GetClosestEnnemy()
{
    float NearestDistance = BIG_NUMBER;

    ACharacterBase *NearestPawn = nullptr;

    for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
    {
        ACharacterBase *OtherPawn = Cast<ACharacterBase>(*Iterator);

        if (OtherPawn != nullptr && OtherPawn != Cast<ACharacterBase>(GetPawn()))
        {
            FVector MyLocation = GetPawn()->GetActorLocation();
            FVector OtherPawnLocation = OtherPawn->GetActorLocation();
            const float TempDistance = FVector::Dist(MyLocation, OtherPawnLocation);
            if (NearestDistance > TempDistance)
            {
                NearestDistance = TempDistance;
                NearestPawn = OtherPawn;
            }
        }
    }

    return NearestPawn;
}