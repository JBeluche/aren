// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/ListView.h"
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

	UPROPERTY(meta = (BindWidget))
	class UButton* B_Build;

	UPROPERTY(meta = (BindWidget))
	UListView* BuildingList;

	UFUNCTION()
	void SwitchToCharacter();

	UFUNCTION()
	void OpenBuildMenu();

	AArenPlayerController* PlayerController;


};
