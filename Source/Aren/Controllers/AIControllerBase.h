// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

class ACharacter;

UCLASS()
class AREN_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	virtual void Tick(float DeltaTime) override;


private:
	virtual void BeginPlay() override;

	ACharacter* ArenCharacter;

	//Attack player
	//Health component

	//Attack zone. Where someone can hit you and you can be hit

	
};
