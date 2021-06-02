// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AREN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

private:

	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float CurrentHealth;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Settings", meta = (AllowPrivateAccess = "true"))
	UAnimMontage*  DyingAnimation;
};
