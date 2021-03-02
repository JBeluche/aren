// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aren/Actors/CharacterBase.h"
#include "ArenCharacter.generated.h"

class ACampPawn;

UCLASS(Blueprintable)
class AArenCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AArenCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Top down camera */
	class UCameraComponent* TopDownCameraComponent;

};

