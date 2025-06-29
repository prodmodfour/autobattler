#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/UnitDataTypes.h" 
#include "UnitCharacter.generated.h"

/**
 * @class AUnitCharacter
 * @brief Represents a single unit character in the game world.
 * @ingroup Units
 */
UCLASS()
class AUTOBATTLER_API AUnitCharacter : public AActor
{
    GENERATED_BODY()

public:
    /**
     * @brief Default constructor.
     */
    AUnitCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    UDataTable* UnitDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    FName UnitID;

    // Begin Stats pulled from Data Table
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float MaxHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float CurrentHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float AttackDamage;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float AttackSpeed;
    // End Stats


protected:
    virtual void BeginPlay() override;

    FUnitData* UnitData;

    void InitializeUnit();
};