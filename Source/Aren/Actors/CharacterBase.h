// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 	

#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"
 	



//Classes
class USphereComponent;
class UAttackComponent;
class UHealthComponent;
class UCharacterCustomizationComponent;


 //Enums
 UENUM(BlueprintType)
 enum class EFaction : uint8 
 {
      NOVARD UMETA(DisplayName = "Novard"),
      RAIDER UMETA(DisplayName = "Raider")
 };

UCLASS()
class AREN_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFaction CurrentFaction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UBehaviorTree* GetBehaviorTree();

	void SetSkeletalMesh(USkeletalMesh* GeneratedSkeletalMesh);
	bool SetToSelectedPlayer();

	void PlayAnimationMontage(UAnimMontage* MontageToPlay, bool bIsLooping);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	USphereComponent* AttackRangeSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UCharacterCustomizationComponent* CharacterCustomizationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bCanBeControlled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bIsSelectedPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
 	UParticleSystem* CircleParticle;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;

//Skeletal meshes

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mask;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;


};
