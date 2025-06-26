#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/UnitDataTypes.h" 
#include "ShopItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class AUTOBATTLER_API UShopItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Shop Item")
    void Setup(const FUnitData& UnitData);

protected:

    UPROPERTY(meta = (BindWidget))
    UImage* Image_Portrait;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_UnitName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Cost;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Buy;
};
