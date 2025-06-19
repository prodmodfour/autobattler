#include "Misc/AutomationTest.h"
#include "Actors/HexGridManager.h" 
#include "Units/UnitCharacter.h"

// A simple way to get a test world for spawning actors if needed
#if WITH_AUTOMATION_TESTS
UWorld* GetTestWorld()
{
    const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
    for (const FWorldContext& Context : WorldContexts)
    {
        if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Game)) && (Context.World() != nullptr))
        {
            return Context.World();
        }
    }
    return nullptr;
}
#endif 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHexGridManagerInitializationTest, "autobattler.Actors.HexGridManager.Initialization", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FHexGridManagerInitializationTest::RunTest(const FString& Parameters)
{
    /* Test 1: Grid initializes with correct dimensions and empty tiles */
    AHexGridManager* GridManager = NewObject<AHexGridManager>(); 
    TestNotNull(TEXT("GridManager should not be null after NewObject"), GridManager);

    int32 TestWidth = 5;
    int32 TestHeight = 4;
    GridManager->InitializeGrid(TestWidth, TestHeight);

    for (int32 y = 0; y < TestHeight; ++y)
    {
        for (int32 x = 0; x < TestWidth; ++x)
        {
            FIntPoint Coords(x,y);
            FHexTileData* Tile = GridManager->GetTileData(Coords);
            TestNotNull(FString::Printf(TEXT("Tile (%d,%d) should exist"), x, y), Tile);
            if (Tile)
            {
                TestNull(FString::Printf(TEXT("Tile (%d,%d) should initially be unoccupied"), x, y), Tile->OccupyingUnit.Get());
                TestEqual(FString::Printf(TEXT("Tile (%d,%d) coordinates should match"), x,y), Tile->GridCoordinates, Coords);
            }
        }
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHexGridManagerBoundsTest, "autobattler.Actors.HexGridManager.BoundsChecking", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FHexGridManagerBoundsTest::RunTest(const FString& Parameters)
{
    /* Test 2: GetTileData handles out-of-bounds coordinates */
    AHexGridManager* GridManager = NewObject<AHexGridManager>();
    GridManager->InitializeGrid(3, 3); 

    TestNull(TEXT("Getting tile data for negative X should return nullptr"), GridManager->GetTileData(FIntPoint(-1, 0)));
    TestNull(TEXT("Getting tile data for excessive X should return nullptr"), GridManager->GetTileData(FIntPoint(3, 0)));
    TestNull(TEXT("Getting tile data for negative Y should return nullptr"), GridManager->GetTileData(FIntPoint(0, -1)));
    TestNull(TEXT("Getting tile data for excessive Y should return nullptr"), GridManager->GetTileData(FIntPoint(0, 3)));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHexGridManagerSetUnitOnTileTest, "autobattler.Actors.HexGridManager.SetUnitOnTile", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FHexGridManagerSetUnitOnTileTest::RunTest(const FString& Parameters)
{
    /* Test 3: Setting and getting a unit on a tile */
    AHexGridManager* GridManager = NewObject<AHexGridManager>();
    GridManager->InitializeGrid(3, 3);
    FIntPoint TestCoords(1,1);

    /* For this test, we don't need a fully functional AUnitCharacter.
    We can even use a dummy UObject castable to AUnitCharacter for pointer identity,
    or just use nullptr and then a valid pointer if AUnitCharacter is simple enough to NewObject.
    For now, let's assume we are setting it to a conceptual unit (even if it's just a placeholder).
    A proper AUnitCharacter might require a UWorld context if it has components that need it.
    Using NewObject<AUnitCharacter>() directly might be problematic if AUnitCharacter has complex needs.
    For this test, we are testing the grid's data management, not the unit itself.
    A nullptr is a valid value for OccupyingUnit. Let's test with an actual object.
    NOTE: Spawning full Actors for LLTs can be tricky. NewObject<UObject> might be safer if
    you only need a unique pointer and can cast. For simplicity, we'll try NewObject<AUnitCharacter>
    but be mindful this can fail if AUnitCharacter is complex.
    A better approach for true unit testing might involve a mock or simpler test double. */

    AUnitCharacter* MockUnit = NewObject<AUnitCharacter>(); // Simplistic; might need a world if AUnitCharacter is complex.
                                                             // If this fails, use a UObject and cast, or mock later.
    TestNotNull(TEXT("MockUnit should be created"), MockUnit);


    bool bSuccess = GridManager->SetUnitOnTile(MockUnit, TestCoords);
    TestTrue(TEXT("SetUnitOnTile should succeed for valid tile"), bSuccess);

    FHexTileData* TileData = GridManager->GetTileData(TestCoords);
    TestNotNull(TEXT("TileData should exist"), TileData);
    if (TileData)
    {
        TestEqual(TEXT("OccupyingUnit should be the MockUnit"), TileData->OccupyingUnit.Get(), MockUnit);
    }

    AUnitCharacter* RetrievedUnit = GridManager->GetUnitAtCoordinates(TestCoords);
    TestEqual(TEXT("GetUnitAtCoordinates should return the MockUnit"), RetrievedUnit, MockUnit);

    // Test setting it to nullptr (clearing the unit)
    GridManager->SetUnitOnTile(nullptr, TestCoords);
    TileData = GridManager->GetTileData(TestCoords); 
    TestNotNull(TEXT("TileData should still exist"), TileData);
    if (TileData)
    {
         TestNull(TEXT("OccupyingUnit should now be nullptr after clearing"), TileData->OccupyingUnit.Get());
    }

    return true;
}