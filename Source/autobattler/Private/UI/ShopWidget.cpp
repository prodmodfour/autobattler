#include "UI/ShopWidget.h" 
#include "Data/UnitDataTypes.h"
#include "UI/ShopItemWidget.h"
#include "Engine/DataTable.h"
#include "Components/HorizontalBox.h"

void UShopWidget::NativeConstruct()
{
    Super::NativeConstruct();
    RefreshShop();
}

void UShopWidget::RefreshShop()
{
    if (!UnitDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("ShopWidget: UnitDataTable is not set!"));
        return;
    }
    if (!ShopItemWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ShopWidget: ShopItemWidgetClass is not set!"));
        return;
    }
    if (!HorizontalBox_ShopItems)
    {
        UE_LOG(LogTemp, Error, TEXT("ShopWidget: HorizontalBox_ShopItems is not bound!"));
        return;
    }

    // --- 1. Clear existing shop items ---
    HorizontalBox_ShopItems->ClearChildren();

    // Get all valid units from the Data Table
    TArray<FUnitData*> AvailableUnits;
    FString ContextString(TEXT("Unit Data Table"));
    TArray<FName> RowNames = UnitDataTable->GetRowNames();

    for (const FName& RowName : RowNames)
    {
        FUnitData* Row = UnitDataTable->FindRow<FUnitData>(RowName, ContextString);
        if (Row)
        {
            AvailableUnits.Add(Row);

        }
    }
    
    if (AvailableUnits.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShopWidget: No available units found in the data table for the current level."));
        return;
    }

    // Randomize and select units for the shop 
    TArray<FUnitData*> ShopOfferings;
    for (int32 i = 0; i < NumShopSlots; ++i)
    {
        if (AvailableUnits.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, AvailableUnits.Num() - 1);
            ShopOfferings.Add(AvailableUnits[RandomIndex]);
        }
    }

    // Create and populate Widgets
    for (FUnitData* UnitData : ShopOfferings)
    {
        if (UnitData)
        {
            UShopItemWidget* ItemWidget = CreateWidget<UShopItemWidget>(this, ShopItemWidgetClass);
            if (ItemWidget)
            {
                ItemWidget->Initialize(*UnitData);
                HorizontalBox_ShopItems->AddChildToHorizontalBox(ItemWidget);
            }
        }
    }
}