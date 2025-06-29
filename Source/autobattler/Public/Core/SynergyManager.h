#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Units/UnitCharacter.h"
#include "SynergyManager.generated.h"

enum class EUnitTrait : uint8;

UCLASS()
class AUTOBATTLER_API USynergyManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    void UpdateSynergies(const TArray<AUnitCharacter*>& UnitsOnBoard);

private:

    TMap<EUnitTrait, int32> ActiveTraitCounts;

    // To eventually be added
    // UPROPERTY()
    // UDataTable* SynergyDataTable;
};
