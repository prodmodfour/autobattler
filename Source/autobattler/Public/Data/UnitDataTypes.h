#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitDataTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;

/**
 * @brief Enum to define the different possible unit traits for synergies.
 */
UENUM(BlueprintType)
enum class EUnitTrait : uint8
{
	Warrior,
	Mage,
	Ranger,
	Tank,
	Assassin
};

/**
 * @brief Defines the data for a single tier of a synergy trait.
 */
USTRUCT(BlueprintType)
struct FTraitLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	int32 RequiredUnitCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText Description;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TSubclassOf<UGameplayEffect> TraitEffect;
};


/**
 * @brief Defines a Synergy Trait, containing its different levels of power.
 * Inherits from FTableRowBase to be used in a Data Table.
 */
USTRUCT(BlueprintType)
struct FTraitData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	EUnitTrait TraitID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TArray<FTraitLevel> TraitLevels;
};


/**
 * @brief Defines a single Unit in the game.
 * Inherits from FTableRowBase to be used in a Data Table.
 */
USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	TSubclassOf<ACharacter> UnitCharacterClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxMana;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	float AttackSpeed;

	// The traits this unit possesses for synergy calculations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Traits")
	TArray<EUnitTrait> Traits;
	
	// The ability this unit can cast
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Ability")
	TSubclassOf<UGameplayAbility> UnitAbility;
};

/**
 * @brief Defines an Item in the game.
 * Inherits from FTableRowBase to be used in a Data Table.
 */
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSubclassOf<UGameplayEffect> EquipEffect;
};