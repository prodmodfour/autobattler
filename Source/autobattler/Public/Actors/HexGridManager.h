#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/HexGridDataTypes.h" 
#include "Units/UnitCharacter.h"
#include "HexGridManager.generated.h"

UCLASS()
class AUTOBATTLER_API AHexGridManager : public AActor
{
    GENERATED_BODY()

public:
    AHexGridManager();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    void InitializeGrid(int32 Width, int32 Height);

    FHexTileData* GetTileData(const FIntPoint& GridCoordinates); 

    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    bool SetUnitOnTile(AUnitCharacter* UnitToPlace, const FIntPoint& GridCoordinates);

    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    AUnitCharacter* GetUnitAtCoordinates(const FIntPoint& GridCoordinates) const;

    UFUNCTION(BlueprintCallable, Category = "Grid Management")
    bool IsTileValid(const FIntPoint& GridCoordinates) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
    int32 GridWidth;

    UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
    int32 GridHeight;

    TArray<FHexTileData> GridTiles;

private:
    int32 GetIndexForCoordinates(const FIntPoint& GridCoordinates) const;
};