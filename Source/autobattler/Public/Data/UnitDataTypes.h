#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitDataTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTexture2D;

UENUM(BlueprintType)
enum class EUnitTrait : uint8
{
	Warrior,
	Mage,
	Ranger,
	Tank,
	Assassin
};

USTRUCT(BlueprintType)
struct FTraitLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	int32 RequiredUnitCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText Description;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TSubclassOf<UGameplayEffect> TraitEffect = nullptr;
};

USTRUCT(BlueprintType)
struct FTraitData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	EUnitTrait TraitID = EUnitTrait::Warrior; // Safe default
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TArray<FTraitLevel> TraitLevels;
};


USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
	TSubclassOf<ACharacter> UnitCharacterClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 MaxMana = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	int32 AttackDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Stats")
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Traits")
	TArray<EUnitTrait> Traits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Ability")
	TSubclassOf<UGameplayAbility> UnitAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
    TObjectPtr<UTexture2D> PortraitTexture = nullptr;
};


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