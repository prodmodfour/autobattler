#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UHorizontalBox;
class UDataTable;
class UShopItemWidget;
struct FUnitData;

UCLASS()
class AUTOBATTLER_API UShopWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Shop")
    void RefreshShop();

protected:
    // Called when the widget is created. We use it to do the initial shop population.
    virtual void NativeConstruct() override;

    // The Data Table containing all possible units.
    // Must be set in the WBP_Shop Blueprint details panel.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Config")
    UDataTable* UnitDataTable;

    // Must be set in the WBP_ShopItem Blueprint details panel.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Config")
    TSubclassOf<UShopItemWidget> ShopItemWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* HorizontalBox_ShopItems;

    UPROPERTY(BlueprintReadOnly, Category = "Shop|Player")
    int32 PlayerLevel = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Shop|Player")
    int32 NumShopSlots = 5;
};
