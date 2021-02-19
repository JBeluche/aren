// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

class ACharacterBase;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AREN_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	UFUNCTION()
	void SetEnnemiesInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	UFUNCTION()
	void RemoveEnnemiesInRange(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	void CheckAttackCondition();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame

	void SetEnnemyToAttack(AActor* NewTarget);
	void RemoveEnnemyToAttack();
	void RemoveFromWaitingList(AActor* ActortoRemove);

	// Variables
	TArray<AActor*> EnemyWaitingList;
	AActor* EnnemyToAttack;
	AActor* CurrentlyAttacking;

	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Settings", meta = (AllowPrivateAccess = "true"))
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	FTimerHandle AttackRateTimerHandle;
	void Attack();

	ACharacterBase* Owner;

		
};
