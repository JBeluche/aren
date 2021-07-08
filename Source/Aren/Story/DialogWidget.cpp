// Copyright CreatingMountains


#include "Aren/Story/DialogWidget.h"

void UDialogWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UDialogWidget::SetData(FText Text)
{
    TB_DialogText->SetText(Text);
}
 