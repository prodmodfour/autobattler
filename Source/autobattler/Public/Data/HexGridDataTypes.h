#pragma once

#include "CoreMinimal.h"
#include "HexGridDataTypes.generated.h" 

class AUnitCharacter;


/**
 * @struct FHexTileData
 * @brief Represents the data for a single tile on the hex grid.
 * @ingroup Data
 */
USTRUCT(BlueprintType) 
struct FHexTileData
{
    GENERATED_BODY() 

    /** @brief The coordinates of the tile on the grid. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    FIntPoint GridCoordinates; 

    /** @brief A weak pointer to the unit currently occupying this tile, if any. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    TWeakObjectPtr<AUnitCharacter> OccupyingUnit;

    /** @brief A flag indicating whether this tile is owned by the player. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    bool bIsPlayerOwned;


     /**
     * @brief Default constructor.
     */
    FHexTileData() : GridCoordinates(FIntPoint::ZeroValue), OccupyingUnit(nullptr), bIsPlayerOwned(false) {}

    /**
     * @brief Constructor that takes coordinates.
     * @param Coordinates The coordinates of the tile on the grid.
     */
    FHexTileData(FIntPoint Coordinates) : GridCoordinates(Coordinates), OccupyingUnit(nullptr), bIsPlayerOwned(false) {}
};