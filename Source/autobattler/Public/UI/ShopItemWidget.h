#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/UnitDataTypes.h" 
#include "ShopItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

/**
 * @class UShopItemWidget
 * @brief Represents a single item in the shop UI.
 * @ingroup UI
 */
UCLASS()
class AUTOBATTLER_API UShopItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * @brief Sets up the widget with the provided unit data.
     * @param UnitData The data of the unit to display.
     */
    UFUNCTION(BlueprintCallable, Category = "Shop Item")
    void Setup(const FUnitData& UnitData);

protected:

    /** @brief The image for the unit's portrait. */
    UPROPERTY(meta = (BindWidget))
    UImage* Image_Portrait;

    /** @brief The text for the unit's name. */
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_UnitName;

    /** @brief The text for the unit's cost. */
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Cost;

    /** @brief The button to buy the unit. */
    UPROPERTY(meta = (BindWidget))
    UButton* Button_Buy;

private:
    /**
     * @brief Handles the loading of the portrait texture.
     */
    void OnPortraitTextureLoaded();
    
    /** @brief A soft pointer to the portrait texture to be loaded. */
    TSoftObjectPtr<UTexture2D> PortraitTextureToLoad;


};