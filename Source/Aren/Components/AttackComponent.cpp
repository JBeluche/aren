// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Components/AttackComponent.h"
#include "Aren/Actors/CharacterBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AttackSpeed = 1.0f;

}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ACharacterBase>(GetOwner());
}

void UAttackComponent::CheckAttackCondition()
{
	//Check if you are not shooting at someone.
	if (!EnnemyToAttack)
	{
		for (int i = 0; i < EnemyWaitingList.Num(); i++)
		{
			//Then check if someone is in waiting list.
			if (Cast<AActor>(EnemyWaitingList[i]))
			{
				//Shoot first one in waiting list
				SetEnnemyToAttack(EnemyWaitingList[i]);
			}
		}
	}
	else if (EnnemyToAttack)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(AttackRateTimerHandle))
		{
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(AttackRateTimerHandle, this, &UAttackComponent::Attack, AttackSpeed, true);
		}
	}
}

void UAttackComponent::SetEnnemiesInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<ACharacterBase>(OtherActor))
	{
		ACharacterBase* OverlappingActor = Cast<ACharacterBase>(OtherActor);
		if(OverlappingActor != Owner && OverlappingActor->CurrentFaction != Owner->CurrentFaction)
		{
		if (!EnnemyToAttack)
		{
			SetEnnemyToAttack(OtherActor);
		}
		else
		{
			EnemyWaitingList.Add(OtherActor);
		}
		}
	}
}

void UAttackComponent::RemoveEnnemiesInRange(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacterBase>(OtherActor))
	{
		ACharacterBase* OverlappingActor = Cast<ACharacterBase>(OtherActor);
		if(OverlappingActor != Owner && OverlappingActor->CurrentFaction != Owner->CurrentFaction)
		{
			if (EnnemyToAttack == OtherActor)
			{
				RemoveEnnemyToAttack();
			}
			else
			{
				RemoveFromWaitingList(OtherActor);
			}
		}
	}
}

void UAttackComponent::SetEnnemyToAttack(AActor *NewEnnemyToAttack)
{
	EnnemyToAttack = NewEnnemyToAttack;
	RemoveFromWaitingList(NewEnnemyToAttack);
}

void UAttackComponent::RemoveEnnemyToAttack()
{
	EnnemyToAttack = nullptr;
}

void UAttackComponent::RemoveFromWaitingList(AActor *ActortoRemove)
{
	for (int i = 0; i < EnemyWaitingList.Num(); i++)
	{
		if (ActortoRemove == Cast<AActor>(EnemyWaitingList[i]))
		{
			EnemyWaitingList.Remove(ActortoRemove);
		}
	}
}

void UAttackComponent::Attack()
{

	UE_LOG(LogTemp, Error, TEXT("Attacking %s"), *EnnemyToAttack->GetName());
	
	UGameplayStatics::ApplyDamage(EnnemyToAttack, Damage, Owner->GetInstigatorController(), Owner, DamageType);
}
