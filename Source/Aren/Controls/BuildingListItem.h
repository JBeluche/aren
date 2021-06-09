// Copyright CreatingMountains

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BuildingListItem.generated.h"

/**
 * 
 */
UCLASS()
class AREN_API UBuildingListItem : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* B_BuildUpgrade;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_NameBuilding;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_BuildUpgrade;
};
