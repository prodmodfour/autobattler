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
	int32 RequiredUnitCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	FText Description;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait")
	TSubclassOf<UGameplayEffect> TraitEffect;
};

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