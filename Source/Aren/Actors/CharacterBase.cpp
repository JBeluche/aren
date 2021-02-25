// Fill out your copyright notice in the Description page of Project Settings.


#include "Aren/Actors/CharacterBase.h"
#include "Components/SphereComponent.h"
#include "Aren/Components/AttackComponent.h"
#include "Aren/Components/HealthComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	AttackRangeSphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(AttackComponent, &UAttackComponent::SetEnnemiesInRange);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(AttackComponent, &UAttackComponent::RemoveEnnemiesInRange);
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackComponent->CheckAttackCondition();



}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



