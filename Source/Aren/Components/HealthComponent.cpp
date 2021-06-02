// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Components/HealthComponent.h"
#include "Aren/Actors/CharacterBase.h"
#include "Aren/Controllers/AIControllerBase.h"


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

	CurrentHealth = DefaultHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Error, TEXT("%s Health is %f"), *GetOwner()->GetName(), CurrentHealth);


	if(CurrentHealth <= 0)
	{
		ACharacterBase * Owner = Cast<ACharacterBase>(GetOwner());

		if(DyingAnimation != nullptr){	Owner->PlayAnimationMontage(DyingAnimation, false);}
		AAIControllerBase* Controller = Cast<AAIControllerBase>(Owner->GetInstigatorController());
		Owner->Destroy();
		Controller->UnPossess();
		//Controller->HandleDeath();
		Controller->Reset();
		

		UE_LOG(LogTemp, Error, TEXT("%s died"), *GetOwner()->GetName());
	}
}
