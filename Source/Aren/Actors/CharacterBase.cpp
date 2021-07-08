// Fill out your copyright notice in the Description page of Project Settings.

#include "Aren/Actors/CharacterBase.h"
#include "Components/SphereComponent.h"
#include "Aren/Components/AttackComponent.h"
#include "Aren/Components/HealthComponent.h"
#include "Aren/Components/CharacterCustomizationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	CharacterCustomizationComponent = CreateDefaultSubobject<UCharacterCustomizationComponent>(TEXT("Character Customization Component"));

	Mask = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mask"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	GetCharacterMovement()->bOrientRotationToMovement = true;


	AttackRangeSphere->SetupAttachment(RootComponent);

	Mask->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(Mask);
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
void ACharacterBase::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::SetSkeletalMesh(USkeletalMesh *GeneratedSkeletalMesh)
{
	SkeletalMesh->SetSkeletalMesh(GeneratedSkeletalMesh, true);
}

bool ACharacterBase::SetToSelectedPlayer()
{
	if (bCanBeControlled)
	{

		bIsSelectedPlayer = true;

		UGameplayStatics::SpawnEmitterAttached(
			CircleParticle,
			SkeletalMesh,			  //mesh to attach to
			FName("MagicCircle"), //socket name
			FVector(0, 0, -85.0f),	  //location relative to socket
			FRotator(0, 0, 0),	  //rotation
			FVector(0.4f, 0.4f, 0.4f), //Scale
			EAttachLocation::KeepRelativeOffset,
			false,
			EPSCPoolMethod::None,
			true);

		return true;
	}
	
	return false;
}


UBehaviorTree* ACharacterBase::GetBehaviorTree()
{
	return AIBehaviorTree;
}

void ACharacterBase::PlayAnimationMontage(UAnimMontage* MontageToPlay, bool bIsLooping)
{
	SkeletalMesh->GetAnimInstance()->Montage_Play(MontageToPlay, 1, EMontagePlayReturnType::MontageLength);
}