// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Components/AttackComponent.h"
#include "Aren/Actors/CharacterBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Aren/Controllers/AIControllerBase.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AttackSpeed = 1.5f;
	AttackingRange = 20.0f;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacterBase>(GetOwner());
}

void UAttackComponent::SetEnnemiesInRange(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<ACharacterBase>(OtherActor))
	{
		ACharacterBase *OverlappingActor = Cast<ACharacterBase>(OtherActor);
		if (OverlappingActor != Owner && OverlappingActor->CurrentFaction != Owner->CurrentFaction)
		{
			DetectedEnemies.Add(OtherActor);
		}
	}
}

void UAttackComponent::RemoveEnnemiesInRange(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacterBase>(OtherActor))
	{
		ACharacterBase *OverlappingActor = Cast<ACharacterBase>(OtherActor);
		if (OverlappingActor != Owner && OverlappingActor->CurrentFaction != Owner->CurrentFaction)
		{
			for (int i = 0; i < DetectedEnemies.Num(); i++)
			{
				if (OverlappingActor == Cast<AActor>(DetectedEnemies[i]))
				{
					DetectedEnemies.Remove(OverlappingActor);
				}
			}
		}
	}
}

void UAttackComponent::CheckAttackCondition()
{
	if (!CharacterBusy)
	{
		NearestEnemy = Cast<ACharacterBase>(GetClosestEnnemyInRange());

		if (NearestEnemy)
		{
			Cast<AAIControllerBase>(Owner->GetController())->SetEnnemyToChase(NearestEnemy);
			const float NearestEnemyDistance = FVector::Dist(NearestEnemy->GetActorLocation(), Owner->GetActorLocation());

			if (NearestEnemyDistance <= AttackingRange)
			{
				if (GetWorld()->GetTimerManager().IsTimerActive(AttackRateTimerHandle))
				{
					Cast<AAIControllerBase>(Owner->GetController())->SetCharacterIsBusy(true);
				}
				else
				{
					GetWorld()->GetTimerManager().SetTimer(AttackRateTimerHandle, this, &UAttackComponent::Attack, AttackSpeed, true);
				}
			}
		}
	}
}

void UAttackComponent::Attack()
{
	if (NearestEnemy)
	{
		//TODO Make the character rotate towards the enemy he attacks
		if(AttackMontage != nullptr){	
			Owner->PlayAnimationMontage(AttackMontage, false);}
			else{
				UE_LOG(LogTemp, Error, TEXT("no montage"));

			}

		UGameplayStatics::ApplyDamage(NearestEnemy, Damage, Owner->GetInstigatorController(), Owner, DamageType);
	}

}

ACharacterBase *UAttackComponent::GetClosestEnnemyInRange()
{
	float NearestDistance = BIG_NUMBER;

	ACharacterBase *NearestPawn = nullptr;

	for (int i = 0; i < DetectedEnemies.Num(); i++)
	{

		if (DetectedEnemies[i] != NULL)
		{
			ACharacterBase *OtherPawn = Cast<ACharacterBase>(DetectedEnemies[i]);

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

	return NearestPawn;
}

