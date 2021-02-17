// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CampControls.generated.h"

class AArenPlayerController;

UCLASS()
class AREN_API UCampControls : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CharacterView;

	UFUNCTION()
	void SwitchToCharacter();

	AArenPlayerController* PlayerController;


};
