#include "SynergyManager.h"
#include "Units/UnitCharacter.h" 

void USynergyManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // Load SynergyDataTable here once created
}

void USynergyManager::UpdateSynergies(const TArray<AUnitCharacter*>& UnitsOnBoard)
{
    ActiveTraitCounts.Empty();

    // 1. Count the active traits from all units on the board. 
    // for (AUnitCharacter* Unit : UnitsOnBoard)
    // {
    //     if(Unit && Unit->UnitData)
    //     {
    //          for (EUnitTrait Trait : Unit->UnitData->Traits)
    //          {
    //              ActiveTraitCounts.FindOrAdd(Trait)++;
    //          }
    //     }
    // }

    // 2. Read the SynergyDataTable to see which buffs should be active.

    // 3. Apply the buffs to the relevant units. 
}