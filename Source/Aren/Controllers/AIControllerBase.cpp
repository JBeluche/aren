// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Controllers/AIControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Aren/Actors/CharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TimerManager.h"

AAIControllerBase::AAIControllerBase()
{
	SetupPerceptionSystem();
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacterBase>(GetPawn());

	if (Owner->GetBehaviorTree() != nullptr)
	{
		AIBehaviorTree = Owner->GetBehaviorTree();
		RunBehaviorTree(AIBehaviorTree);

		GetBlackboardComponent()->SetValueAsVector(TEXT("DesignatedLocation"), FVector(-13718.016602, -1182.054199, 224.229675));

		//Start a timer (Set closest enemy)
		GetWorld()->GetTimerManager().SetTimer(GetClosestEnemyTimerHandle, this, &AAIControllerBase::SetClosestEnemy, 0.5f, true);
	}
}

void AAIControllerBase::SetClosestEnemy()
{
	TArray<AActor *> PerceivedActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(TSubclassOf<UAISense_Sight>(), PerceivedActors);
	if (PerceivedActors.Num() > 0 && Owner != nullptr)
	{

		GetBlackboardComponent()->SetValueAsObject(TEXT("ClosestEnemy"), GetClosestEnnemyInRange(PerceivedActors));
	}
}

void AAIControllerBase::Tick(float DeltaTime)
{
}

ACharacterBase *AAIControllerBase::GetClosestEnnemyInRange(TArray<AActor *> ArrayOfActors)
{
	float NearestDistance = BIG_NUMBER;

	ACharacterBase *NearestPawn = nullptr;

	for (int i = 0; i < ArrayOfActors.Num(); i++)
	{

		if (ArrayOfActors[i] != NULL)
		{
			ACharacterBase *OtherPawn = Cast<ACharacterBase>(ArrayOfActors[i]);

			if (OtherPawn != nullptr && OtherPawn != Owner && OtherPawn->CurrentFaction != Owner->CurrentFaction)
			{
				FVector MyLocation = Owner->GetActorLocation();
				FVector OtherPawnLocation = OtherPawn->GetActorLocation();
				const float TempDistance = FVector::Dist(MyLocation, OtherPawnLocation);
				if (NearestDistance > TempDistance)
				{
					NearestDistance = TempDistance;
					NearestPawn = OtherPawn;
				}
			}
		}
	}
	if (NearestPawn == nullptr)
	{
	}

	return NearestPawn;
}

void AAIControllerBase::SetEnnemyToChase(ACharacterBase *AttackTarget)
{
	if (Owner->GetBehaviorTree() != nullptr)
	{
		GetBlackboardComponent()->SetValueAsObject(TEXT("AttackTarget"), AttackTarget);
	}
}

void AAIControllerBase::SetCharacterIsBusy(bool IsBusy)
{
	if (Owner->GetBehaviorTree() != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("Busy"), true);
	}
}

bool AAIControllerBase::GetCharacterIsBusy()
{
	if (Owner != nullptr)
	{
		if (Owner->GetBehaviorTree() != nullptr)
		{
			return GetBlackboardComponent()->GetValueAsBool(TEXT("Busy"));
		}
	}

	return false;
}

void AAIControllerBase::SetupPerceptionSystem()
{
	// create and initialise sight configuration object
	SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	if (SightConfiguration)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfiguration->SightRadius = 1500.0f;
		SightConfiguration->LoseSightRadius = SightConfiguration->SightRadius + 25.0f;
		SightConfiguration->PeripheralVisionAngleDegrees = 180.0f;
		SightConfiguration->SetMaxAge(5.0f);
		SightConfiguration->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
		SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;

		// add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*SightConfiguration->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfiguration);
	}
}

void AAIControllerBase::HandleDeath()
{
	GetBlackboardComponent()->ClearValue(TEXT("ClosestEnemy"));
}