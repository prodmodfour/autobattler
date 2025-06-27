#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UHorizontalBox;
class UDataTable;
class UShopItemWidget;
struct FUnitData;

/**
 * @class UShopWidget
 * @brief Represents the shop UI, which displays a selection of units for the player to purchase.
 * @ingroup UI
 */
UCLASS()
class AUTOBATTLER_API UShopWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * @brief Refreshes the shop with a new selection of units.
     */
    UFUNCTION(BlueprintCallable, Category = "Shop")
    void RefreshShop();

protected:
    /**
     * @brief Called when the widget is created.
     */
    virtual void NativeConstruct() override;

    /** @brief The data table containing all possible units. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Config")
    UDataTable* UnitDataTable;

    /** @brief The class of the shop item widget to spawn. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Config")
    TSubclassOf<UShopItemWidget> ShopItemWidgetClass;

    /** @brief The horizontal box that contains the shop items. */
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* HorizontalBox_ShopItems;

    /** @brief The current level of the player. */
    UPROPERTY(BlueprintReadOnly, Category = "Shop|Player")
    int32 PlayerLevel = 1;

    /** @brief The number of shop slots available to the player. */
    UPROPERTY(BlueprintReadOnly, Category = "Shop|Player")
    int32 NumShopSlots = 5;
};