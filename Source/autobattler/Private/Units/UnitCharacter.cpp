#include "Units/UnitCharacter.h"
#include "Engine/DataTable.h"

AUnitCharacter::AUnitCharacter()
{
    // Set default values if needed
    UnitDataTable = nullptr;
    UnitData = nullptr;
    MaxHealth = 100.f;
    CurrentHealth = 100.f;
    AttackDamage = 10.f;
    AttackSpeed = 1.f;
}

void AUnitCharacter::BeginPlay()
{
    Super::BeginPlay();
    InitializeUnit();
}

void AUnitCharacter::InitializeUnit()
{
    if (UnitDataTable && UnitID != NAME_None)
    {
        static const FString ContextString(TEXT("Unit Data"));
        UnitData = UnitDataTable->FindRow<FUnitData>(UnitID, ContextString);

        if (UnitData)
        {
            MaxHealth = UnitData->MaxHealth;
            CurrentHealth = MaxHealth;
            AttackDamage = UnitData->AttackDamage;
            AttackSpeed = UnitData->AttackSpeed;

        }
    }
}