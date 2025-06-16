#pragma once

#include "CoreMinimal.h"
#include "HexGridDataTypes.generated.h" 

class AUnitCharacter;

USTRUCT(BlueprintType) 
struct FHexTileData
{
    GENERATED_BODY() 

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    FIntPoint GridCoordinates; 

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    TWeakObjectPtr<AUnitCharacter> OccupyingUnit;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    bool bIsPlayerOwned;


    FHexTileData() : GridCoordinates(FIntPoint::ZeroValue), OccupyingUnit(nullptr), bIsPlayerOwned(false) {}
    FHexTileData(FIntPoint Coordinates) : GridCoordinates(Coordinates), OccupyingUnit(nullptr), bIsPlayerOwned(false) {}
};