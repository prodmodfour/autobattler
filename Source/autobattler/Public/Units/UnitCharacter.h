#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
};