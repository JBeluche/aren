// Copyright CreatingMountains

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class AREN_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_DialogText;

	void SetData(FText Text);

	
};
