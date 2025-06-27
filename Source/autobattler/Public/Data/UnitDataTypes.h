#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitDataTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTexture2D;

/**
 * @enum EUnitTrait
 * @brief Defines the possible traits a unit can have.
 * @ingroup Data
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
 * @struct FTraitLevel
 * @brief Represents a single level of a trait, including the required unit count and the effect it provides.
 * @ingroup Data
 */
USTRUCT(BlueprintType)
struct FTraitLevel
{
	GENERATED_BODY()

	/** @brief The number of units required to activate this trait level. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	int32 RequiredUnitCount = 0;

	/** @brief The description of the trait level. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText Description;


	/** @brief The gameplay effect to apply when this trait level is active. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TSubclassOf<UGameplayEffect> TraitEffect = nullptr;
};

/**
 * @struct FTraitData
 * @brief Represents the data for a single trait, including its ID, display name, and levels.
 * @ingroup Data
 */
USTRUCT(BlueprintType)
struct FTraitData : public FTableRowBase
{
	GENERATED_BODY()

	/** @brief The ID of the trait. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	EUnitTrait TraitID = EUnitTrait::Warrior; // Safe default
	
	/** @brief The display name of the trait. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText DisplayName;

	/** @brief The different levels of this trait. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TArray<FTraitLevel> TraitLevels;
};


/**
 * @struct FUnitData
 * @brief Represents the data for a single unit, including its stats, traits, and abilities.
 * @ingroup Data
 */
USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

	/** @brief The display name of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	FText DisplayName;

	/** @brief The cost of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	int32 Cost = 0;

	/** @brief The character class to spawn for this unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	TSubclassOf<ACharacter> UnitCharacterClass;
	
	/** @brief The maximum health of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxHealth = 100;

	/** @brief The maximum mana of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxMana = 100;
	
	/** @brief The attack damage of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 AttackDamage = 10;

	/** @brief The attack speed of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	float AttackSpeed = 1.0f;

	/** @brief The traits of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Traits")
	TArray<EUnitTrait> Traits;

	/** @brief The ability of the unit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Ability")
	TSubclassOf<UGameplayAbility> UnitAbility;

	/** @brief The portrait texture of the unit. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
    TSoftObjectPtr<UTexture2D> PortraitTexture = nullptr;
};


/**
 * @struct FItemData
 * @brief Represents the data for a single item, including its name, description, and the effect it provides.
 * @ingroup Data
 */
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	/** @brief The display name of the item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText DisplayName;

	/** @brief The description of the item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText Description;

	/** @brief The gameplay effect to apply when this item is equipped. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSubclassOf<UGameplayEffect> EquipEffect;
};