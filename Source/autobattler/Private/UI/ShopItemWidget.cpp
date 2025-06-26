#include "UI/ShopItemWidget.h" 
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UShopItemWidget::Setup(const FUnitData& UnitData)
{
    if (Text_UnitName)
    {
        Text_UnitName->SetText(UnitData.DisplayName);
    }

    if (Text_Cost)
    {
        Text_Cost->SetText(FText::AsNumber(UnitData.Cost));
    }

    if (Image_Portrait)
    {
        Image_Portrait->SetBrushFromTexture(UnitData.PortraitTexture);
    }
}