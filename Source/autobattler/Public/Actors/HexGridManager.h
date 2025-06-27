#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/HexGridDataTypes.h" 
#include "Units/UnitCharacter.h"
#include "HexGridManager.generated.h"

/**
 * @class AHexGridManager
 * @brief Manages the hex grid for the game, including tile data and unit placement.
 * @ingroup Actors
 */
UCLASS()
class AUTOBATTLER_API AHexGridManager : public AActor
{
    GENERATED_BODY()

public:
    /**
     * @brief Default constructor.
     */
    AHexGridManager();

    /**
     * @brief Called when the game starts or when spawned.
     */
    virtual void BeginPlay() override;

    /**
     * @brief Initializes the grid with the specified width and height.
     * @param Width The width of the grid.
     * @param Height The height of the grid.
     */
    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    void InitializeGrid(int32 Width, int32 Height);

    /**
     * @brief Gets the data for a tile at the specified coordinates.
     * @param GridCoordinates The coordinates of the tile.
     * @return A pointer to the tile data, or nullptr if the coordinates are invalid.
     */
    FHexTileData* GetTileData(const FIntPoint& GridCoordinates); 

    /**
     * @brief Places a unit on a tile at the specified coordinates.
     * @param UnitToPlace The unit to place on the tile.
     * @param GridCoordinates The coordinates of the tile.
     * @return True if the unit was placed successfully, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    bool SetUnitOnTile(AUnitCharacter* UnitToPlace, const FIntPoint& GridCoordinates);

    /**
     * @brief Gets the unit at the specified coordinates.
     * @param GridCoordinates The coordinates of the tile.
     * @return A pointer to the unit, or nullptr if there is no unit at the specified coordinates.
     */
    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    AUnitCharacter* GetUnitAtCoordinates(const FIntPoint& GridCoordinates) const;

    /**
     * @brief Checks if a tile at the specified coordinates is valid.
     * @param GridCoordinates The coordinates of the tile.
     * @return True if the tile is valid, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    bool IsTileValid(const FIntPoint& GridCoordinates) const;

protected:
    /** @brief The width of the grid. */
    UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
    int32 GridWidth;

    /** @brief The height of the grid. */
    UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
    int32 GridHeight;

    /** @brief An array of all the tiles on the grid. */
    TArray<FHexTileData> GridTiles;

private:
    /**
     * @brief Gets the index in the GridTiles array for the specified coordinates.
     * @param GridCoordinates The coordinates of the tile.
     * @return The index of the tile in the GridTiles array.
     */
    int32 GetIndexForCoordinates(const FIntPoint& GridCoordinates) const;
};