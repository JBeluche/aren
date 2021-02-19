// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{

	Super::BeginPlay();

	Health = DefaultHealth;

	//GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	
}


void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	UE_LOG(LogTemp, Error, TEXT("Losing health %f"), Damage);
	if(Damage == 0)
	{
		

		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if(Health <= 0)
	{
UE_LOG(LogTemp, Error, TEXT("I am dead"));

		/*if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to game mode"));
		}*/
	}
}