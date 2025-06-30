#if WITH_DEV_AUTOMATION_TESTS
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Engine/World.h"
#include "Units/UnitCharacter.h" 
#include "Engine/DataTable.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCombatSystemTest, "Autobattler.Tests.Combat.UnitInitialization", 
                                EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter);

bool FCombatSystemTest::RunTest(const FString& Parameters)
{

    UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();


    UDataTable* UnitDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Autobattler/Data/DT_Units.DT_Units"));
    TestNotNull(TEXT("Unit DataTable should be loaded"), UnitDataTable);

    AUnitCharacter* TestUnit = World->SpawnActor<AUnitCharacter>();
    TestNotNull(TEXT("TestUnit should be successfully spawned"), TestUnit);

    TestUnit->UnitDataTable = UnitDataTable;
    TestUnit->UnitID = FName("TestWarrior");

    TestUnit->DispatchBeginPlay();

    FUnitData* TestWarriorData = UnitDataTable->FindRow<FUnitData>(FName("TestWarrior"), "");
    TestEqual(TEXT("Unit's health should be initialized from DataTable"), TestUnit->CurrentHealth, TestWarriorData->MaxHealth);

    return true;
}
#endif