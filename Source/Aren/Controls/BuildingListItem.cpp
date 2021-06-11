// Copyright CreatingMountains

#include "Aren/Controls/BuildingListItem.h"

void UBuildingListItem::NativeConstruct()
{
    Super::NativeConstruct();
    TB_NameBuilding->SetText(FText::FromString(this->GetName()));
    UE_LOG(LogTemp, Error, TEXT("Name 11 of widget is: %s"), *GetName());

}

void UBuildingListItem::SetData(FText Text)
{
    TB_NameBuilding->SetText(Text);
    UE_LOG(LogTemp, Error, TEXT("Name 22 of widget is: %s"), *GetName());

}
 