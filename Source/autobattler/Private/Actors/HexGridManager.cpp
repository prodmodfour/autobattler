#include "autobattler.h"
#include "Actors/HexGridManager.h"

AHexGridManager::AHexGridManager()
{
    PrimaryActorTick.bCanEverTick = false;
    /* This is the same size as other autochess style games like dota autochess and TFT */
    GridWidth = 7;  
    GridHeight = 8; 

}

void AHexGridManager::BeginPlay()
{
    Super::BeginPlay();
    InitializeGrid(GridWidth, GridHeight); 
}

void AHexGridManager::InitializeGrid(int32 Width, int32 Height)
{
    GridWidth = Width;
    GridHeight = Height;
    GridTiles.Empty();
    GridTiles.SetNum(GridWidth * GridHeight); 

    for (int32 y = 0; y < GridHeight; ++y)
    {
        for (int32 x = 0; x < GridWidth; ++x)
        {
            FIntPoint Coords(x, y);
            GridTiles[GetIndexForCoordinates(Coords)] = FHexTileData(Coords);
        }
    }
}

FHexTileData* AHexGridManager::GetTileData(const FIntPoint& GridCoordinates)
{
    if (!IsTileValid(GridCoordinates))
    {
        return nullptr;
    }
    return &GridTiles[GetIndexForCoordinates(GridCoordinates)];
}

bool AHexGridManager::SetUnitOnTile(AUnitCharacter* UnitToPlace, const FIntPoint& GridCoordinates)
{
    FHexTileData* Tile = GetTileData(GridCoordinates);
    if (Tile /* && Tile->OccupyingUnit == nullptr */) // Add occupation check later if needed by tests
    {
        Tile->OccupyingUnit = UnitToPlace;
        return true;
    }
    return false;
}

AUnitCharacter* AHexGridManager::GetUnitAtCoordinates(const FIntPoint& GridCoordinates) const
{
    if (!IsTileValid(GridCoordinates))
    {
        return nullptr;
    }
    return GridTiles[GetIndexForCoordinates(GridCoordinates)].OccupyingUnit.Get();
}

bool AHexGridManager::IsTileValid(const FIntPoint& GridCoordinates) const
{
    return GridCoordinates.X >= 0 && GridCoordinates.X < GridWidth &&
           GridCoordinates.Y >= 0 && GridCoordinates.Y < GridHeight;
}

int32 AHexGridManager::GetIndexForCoordinates(const FIntPoint& GridCoordinates) const
{
    return GridCoordinates.Y * GridWidth + GridCoordinates.X;
}