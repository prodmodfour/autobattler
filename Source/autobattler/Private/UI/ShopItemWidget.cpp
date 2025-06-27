#include "UI/ShopItemWidget.h" 
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h" 


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


    PortraitTextureToLoad = UnitData.PortraitTexture;
    
    if (PortraitTextureToLoad.IsPending())
    {
        FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
        StreamableManager.RequestAsyncLoad(PortraitTextureToLoad.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UShopItemWidget::OnPortraitTextureLoaded));
    }
    else
    {

        OnPortraitTextureLoaded();
    }
}

void UShopItemWidget::OnPortraitTextureLoaded()
{
    if (PortraitTextureToLoad.IsValid())
    {
        Image_Portrait->SetBrushFromTexture(PortraitTextureToLoad.Get());
    }
}