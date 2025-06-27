#include "UI/ShopItemWidget.h" 
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h" 

DEFINE_LOG_CATEGORY_STATIC(LogShopWidget, All, All);

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
    UE_LOG(LogShopWidget, Log, TEXT("Setup called for unit. Attempting to load texture: %s"), *PortraitTextureToLoad.ToString());
    
    if (PortraitTextureToLoad.IsPending())
    {
        UE_LOG(LogShopWidget, Log, TEXT("Texture is pending, requesting async load."));
        FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
        StreamableManager.RequestAsyncLoad(PortraitTextureToLoad.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UShopItemWidget::OnPortraitTextureLoaded));
    }
    else
    {
        UE_LOG(LogShopWidget, Log, TEXT("Texture was not pending, calling OnPortraitTextureLoaded directly."));
        OnPortraitTextureLoaded();
    }
}

void UShopItemWidget::OnPortraitTextureLoaded()
{
    UE_LOG(LogShopWidget, Log, TEXT("OnPortraitTextureLoaded called."));
    if (PortraitTextureToLoad.IsValid())
    {
        UE_LOG(LogShopWidget, Log, TEXT("Texture is valid, setting brush."));
        Image_Portrait->SetBrushFromTexture(PortraitTextureToLoad.Get());
    }
    else
    {
       UE_LOG(LogShopWidget, Warning, TEXT("Texture is NOT valid after attempting to load!"));
    }
}