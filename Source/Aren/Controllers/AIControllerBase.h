// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

class ACharacterBase;

UCLASS()
class AREN_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	virtual void Tick(float DeltaTime) override;
	
	void SetCharacterIsBusy(bool IsBusy);
	bool GetCharacterIsBusy();
	void SetEnnemyToChase(ACharacterBase* AttackTarget);
	void HandleDeath();

private:
	virtual void BeginPlay() override;

	ACharacterBase *GetClosestEnnemyInRange(TArray<AActor*> ArrayOfActors);

	class UAISenseConfig_Sight* SightConfiguration;

	ACharacterBase* PendingTarget;
	UBehaviorTree* AIBehaviorTree;
	FTimerHandle GetClosestEnemyTimerHandle;

	void SetClosestEnemy();
	void SetupPerceptionSystem();

	ACharacterBase* Owner; 

};
