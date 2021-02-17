// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacterControls.generated.h"

class AArenPlayerController;

UCLASS()
class AREN_API UMainCharacterControls : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CampView;

	UFUNCTION()
	void SwitchToCamp();

	AArenPlayerController* PlayerController;


	
};
