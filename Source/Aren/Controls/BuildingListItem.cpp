// Copyright CreatingMountains

#include "Aren/Controls/BuildingListItem.h"

void UBuildingListItem::NativeConstruct()
{
    Super::NativeConstruct();
    TB_NameBuilding->SetText(FText::FromString(this->GetName()));

}

void UBuildingListItem::SetData(FText Text)
{
    TB_NameBuilding->SetText(Text);

}
 