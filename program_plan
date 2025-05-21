Building Your Own Auto Battler: A C++ Developer's Guide to Unreal Engine 5I. Introduction: Laying the FoundationThe auto-battler genre, popularized by titles like Teamfight Tactics (TFT), offers a unique blend of strategy, resource management, and automated combat. This guide provides a comprehensive, step-by-step approach for C++ developers to construct a similar game within Unreal Engine 5 (UE5). The focus will be on implementing the core mechanics using C++, leveraging the engine's powerful features to bring this complex genre to life.A. Overview of Teamfight Tactics (TFT) Mechanics for ReplicationTo successfully replicate a TFT-like experience, a clear understanding of its core gameplay loop is essential. Players assemble teams of champions, strategically positioning them on a hexagonal battlefield. These teams then engage in automated combat rounds against opponents or AI-controlled enemies (PvE rounds). Key mechanics that define the TFT experience include :
Game Phases: The game progresses through distinct phases:

Shared Draft (Carousel): Players pick champions and items from a rotating pool, with lower-health players getting earlier picks.
Preparation Phase: Players use gold to buy champions from a shared shop, upgrade them by collecting multiples, equip items, and arrange their team on their side of the board.
Combat Phase: Units automatically fight the opponent's team or PvE enemies.
PvE Rounds: Special rounds against AI enemies that can drop gold, champions, or items.


Economy: Gold is the primary resource, earned passively each round, through interest (earning extra gold for saved gold, capped), and via win/loss streak bonuses. Gold is spent on buying champions, rerolling the shop, and purchasing experience points (XP) to level up. Leveling up increases the number of units a player can field and improves the odds of finding higher-cost, rarer units in the shop.
Units (Champions):

Cost and Rarity: Units have different gold costs (typically 1 to 5), indicating their rarity and general power level.
Star Levels: Collecting three identical 1-star units upgrades them to a 2-star version. Three identical 2-star units combine into a powerful 3-star version.
Traits (Origins/Classes): Each unit possesses multiple traits. Fielding several units with the same trait activates powerful synergistic bonuses that can strengthen allies or weaken enemies.
Abilities: Most units have a unique ability that they cast upon reaching full mana. Mana is typically gained by attacking and taking damage.


Items:

Components: Basic items offering minor stat boosts.
Completed Items: Combining two component items creates a more powerful completed item with enhanced stats and unique effects. Items are crucial for augmenting unit capabilities.


Player Health: Each player has a health pool. Losing a combat round results in taking damage based on the number and strength of surviving enemy units. The last player with health remaining wins.
These mechanics, as detailed in sources like the Teamfight Tactics Wikipedia page , form the foundational blueprint for the systems that will be developed in this guide.B. Why Unreal Engine 5 and C++?Unreal Engine 5 stands as a premier choice for developing a game of this nature due to its advanced rendering capabilities, comprehensive suite of development tools, and a robust C++ API that allows for deep engine control. For an auto-battler, which involves numerous units, complex ability interactions, and potentially intricate calculations for stats and synergies, UE5's features are particularly advantageous. The engine's Gameplay Ability System (GAS), for instance, is well-suited for managing the diverse abilities and status effects inherent in TFT-like champions and items.Opting for C++ as the primary development language unlocks the full potential of Unreal Engine.2 C++ provides the performance necessary for handling the potentially large number of units and real-time combat calculations. It allows for the creation of highly optimized, scalable systems, which is critical for a game that simulates many interactions simultaneously. While UE5 also offers Blueprint visual scripting for rapid prototyping and certain tasks, C++ remains the backbone for performance-intensive logic and complex system architecture.C. Essential Engine Setup and PluginsBefore diving into code, some initial engine configuration is beneficial. A key consideration for a game with complex character abilities and attributes is the Gameplay Ability System (GAS). If chosen, the GameplayAbilities plugin should be enabled early in the project's lifecycle. This can be done through the editor's plugin menu (Edit > Plugins, then search for Gameplay Abilities and enable it, followed by an editor restart).3Enabling GAS from the outset allows for a more integrated and streamlined approach to designing units, their statistics, and their abilities.3 GAS provides foundational classes like UAttributeSet for defining and managing numerical stats (e.g., Health, Mana, Attack Damage) and UGameplayAbility for creating active and passive skills. These systems are designed to work cohesively, including built-in support for network replication, which is invaluable if multiplayer functionality is a future goal. By integrating GAS early, unit development can leverage these powerful features from the beginning, leading to cleaner, more maintainable code and reducing the need for significant refactoring later. For example, core unit attributes like health and mana can be implemented as GAS attributes, and champion skills can be directly implemented as Gameplay Abilities, complete with costs, cooldowns, and complex effect applications.Other plugins, such as CommonUI for more advanced user interface development 5, might become relevant as the project expands. However, for the initial stages, the focus will be on UMG (Unreal Motion Graphics) basics driven by C++.II. Project Setup and Core C++ ArchitectureA solid foundation is paramount for a project of this scope. This section details the creation of the Unreal Engine 5 project and the establishment of a core C++ architecture tailored for an auto-battler.A. Creating a New UE5 C++ ProjectThe first step is to create a new project in Unreal Engine 5.
Launch the Unreal Editor.
In the Project Browser, select the "Games" category.
Choose a suitable template. The "Blank" template with "C++" selected is often a good starting point as it provides a minimal setup, allowing for a custom architecture from the ground up.6 Ensure "Starter Content" can be disabled if not needed, to keep the project clean.
Specify the project location and name (e.g., "TFTClone").
Click "Create Project". Unreal Engine will generate the necessary project files and open the solution in your configured C++ Integrated Development Environment (IDE), such as Visual Studio or Rider.
B. Recommended Project StructureA well-organized project structure is crucial for maintainability, especially as the game's complexity grows. Within the Source/[YourProjectName] directory, a logical hierarchy of folders should be established. Consider the following structure as a starting point:
Source/[YourProjectName]/

Public/ (Public header files)
Private/ (Private C++ source files)
Core/ (Fundamental game logic, main GameMode, GameState)
Pawns/ or Units/ (Base unit classes, specific unit types)
Actors/ (Other gameplay actors, e.g., GridManager, Projectiles)
Components/ (Reusable ActorComponents, e.g., HealthComponent if not using GAS, ShopManagerComponent)
Player/ (PlayerController, PlayerState)
UI/ (Base UMG widget C++ classes)
Systems/ (Subfolders for distinct systems like Economy, Items, Synergies)
Data/ (Structs for DataTables, Enums)


This structure promotes modularity and encapsulation, aligning with principles discussed for better code practices.2 Adhering to Unreal Engine's naming conventions is equally important for clarity and consistency.7 For instance, classes deriving from AActor should be prefixed with A (e.g., AUnitCharacter), and classes deriving from UObject (including UActorComponent and UUserWidget) with U (e.g., UShopManagerComponent, UPlayerHUDWidget). A consistent naming scheme, as outlined in Epic's C++ Coding Standard 7, significantly reduces ambiguity and enhances code readability, making it easier for developers to understand the role and type of different classes. A GitHub example for a general UE5 file structure can also provide practical insights.8Organizing the project logically from the start prevents it from becoming difficult to navigate, a common pitfall in complex game development. Given that a TFT clone involves numerous interconnected systems (units, items, economy, combat, UI), a clear folder structure helps developers locate and manage the code for each system efficiently.C. Defining Core C++ Gameplay ClassesThe Unreal Engine Gameplay Framework provides a set of base classes that serve as building blocks for game structure. For our TFT clone, we will define custom C++ classes inheriting from these framework classes:
Class NameUE Base ClassKey Responsibilities in TFT CloneATFTGameModeBaseAGameModeBaseManages game rules, round progression (Preparation, Combat, Carousel, PvE phases), unit spawning for shop/carousel/PvE rounds, and determines win/loss conditions for rounds and the overall game. Server-authoritative. 9ATFTGameStateBaseAGameStateBaseReplicates critical game state to all clients. This includes the current round number, current game phase (e.g., Preparation, Combat), the shared unit pool for the shop, and potentially lists of active players. 9ATFTPlayerControllerAPlayerControllerHandles player input for actions such as buying/selling units, placing units on the board, rerolling the shop, locking the shop, buying XP, and interacting with various UI elements. 11ATFTPlayerStateAPlayerStateStores player-specific persistent data like current gold, experience points (XP), player level, and player health. If using GAS, the UAbilitySystemComponent is often best placed here. 1AUnitCharacterACharacter/APawnBase class for all combat units. Manages unit-specific data (stats, abilities, items) and behavior. (Detailed in Section IV). 6
The choice between AGameModeBase and its more feature-rich counterpart AGameMode (which includes a built-in match state machine 9) is an important architectural decision. While AGameMode's state machine could be adapted, TFT's game loop involves very specific and distinct phases (Carousel, PvE, PvP Preparation, PvP Combat). Implementing a custom state machine using an enum (e.g., ETFTPhase) within ATFTGameModeBase and ATFTGameStateBase often provides finer-grained control and clearer logic for these unique phases. ATFTGameModeBase would then contain functions to manage transitions (e.g., Server_StartPreparationPhase(), Server_BeginCombatPhase()), and ATFTGameStateBase would replicate the current ETFTPhase to clients, primarily for UI updates and controlling client-side logic.D. Introduction to Unreal Engine's Gameplay FrameworkUnderstanding the interaction between these core classes is fundamental to Unreal Engine development.13
The GameMode (ATFTGameModeBase) exists only on the server (or the host in a listen-server setup) and defines the rules of the game. It's responsible for the game's flow, managing transitions between different states or phases.
The GameState (ATFTGameStateBase) exists on the server and is replicated to all connected clients. It holds the state of the game that all players need to be aware of, such as the current round, active players, or scores. UI elements frequently query the GameState for information to display.
The PlayerController (ATFTPlayerController) represents the human player's interface to the game. It handles input and translates it into actions within the game world. In a server-client architecture, PlayerControllers exist on the server for every player and on the owning client for that specific player.
The PlayerState (ATFTPlayerState) stores information about a particular player that needs to be replicated to all clients, such as their name, score, gold, or current level. It persists throughout the game, even if the player's controlled Pawn changes.
Pawns/Characters (AUnitCharacter) are actors that can be controlled by a player or AI. They are the physical representation of entities in the game world.
Even when developing a primarily single-player game, structuring the project with the server-client model in mind (where the GameMode is server-authoritative and GameState replicates information) is a good practice.9 This approach promotes a clear separation of concerns and makes potential future transitions to multiplayer significantly smoother.III. The Arena: Implementing the Hexagonal Grid (C++)The hexagonal grid is the battlefield where units are placed and combat unfolds. A robust C++ implementation of this grid is essential for core gameplay mechanics. TFT uses a hexagonal grid for unit placement.A. Designing the Grid Data StructureA dedicated AActor subclass, let's call it AHexGridManager, will be responsible for owning and managing the grid logic. This manager will contain the primary data structure representing the grid.
Grid Representation: A common approach is to use a one-dimensional array to store data for each tile, with helper functions to convert 2D grid coordinates to a 1D index.
C++// In HexGridManager.h
USTRUCT(BlueprintType)
struct FHexTileData
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    FIntPoint GridCoordinates; // Axial or Offset coordinates

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    TWeakObjectPtr<AUnitCharacter> OccupyingUnit; // Pointer to the unit on this tile

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Data")
    bool bIsPlayerOwned; // Is this tile on the player's side or opponent's?

    // Add other relevant tile properties, e.g., special effects, terrain type
};

// In AHexGridManager.h
UPROPERTY()
TArray<FHexTileData> GridTiles;

UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
int32 GridWidth;

UPROPERTY(EditDefaultsOnly, Category = "Grid Setup")
int32 GridHeight; // For a typical TFT board, half player, half opponent

The TWeakObjectPtr for OccupyingUnit is a safer choice than a raw pointer, as it won't prevent the unit from being garbage collected if it's destroyed, avoiding dangling pointers. The choice of coordinate system (axial, cube, or offset) for FIntPoint GridCoordinates is important. Axial or cube coordinates often simplify hexagonal mathematics like neighbor finding and distance calculations significantly.15 A forum post provides a practical UE implementation example using an ATileMap actor and storing ATile actor pointers, where each ATile can hold a reference to a unit.16
B. Procedural Hexagonal Grid GenerationThe visual representation of the grid can be generated procedurally within the AHexGridManager.

Generation Logic: This logic, likely in AHexGridManager::OnConstruction (for editor preview) or AHexGridManager::BeginPlay (for runtime generation), will iterate through the defined grid dimensions.


Tile Visuals:

Instanced Static Meshes (ISMs): For performance, especially with many tiles, ISMs are recommended. A single UInstancedStaticMeshComponent can render all hex tiles with minimal draw calls. The AHexGridManager would add instances to this component at the calculated world positions of each tile. The ATileMap example from the forum post utilizes ISMs.16
Individual Actors: If tiles require complex individual behaviors or frequent unique visual changes, spawning them as separate AActor instances (e.g., AHexTile actor) is an alternative, though with higher performance overhead. Given TFT's relatively static tiles, ISMs are generally preferable for the visual layer.



World Position Calculation: A crucial function will convert grid coordinates (e.g., axial q, r) to world space FVector positions. This involves constants related to hexagon geometry (like 3​/2 for offsets). The Red Blob Games guide on hexagon grids provides excellent mathematical formulas and C++ examples for this.15 A YouTube tutorial also demonstrates dynamic board creation 18, and others show specific hexagonal grid generation techniques.19
The decision between ISMs and individual actors for tiles hinges on the trade-off between performance and per-tile flexibility. Since TFT tiles are primarily static placeholders, ISMs offer significant performance benefits by minimizing draw calls. The game logic can still operate on the FHexTileData array, which is separate from the visual representation. If, hypothetically, tiles needed to animate independently or have unique, frequently changing materials, individual actors might simplify such logic at the cost of rendering performance.

C. Unit Placement and Movement Logic (Preparation Phase)During the preparation phase, players arrange units on their side of the board.
Player Interaction: The ATFTPlayerController will handle input for selecting a unit (from the bench) and a target tile on the player's half of the grid.
Grid Manager Functions: The AHexGridManager will provide public C++ functions to facilitate this:
C++// In AHexGridManager.h
UFUNCTION(BlueprintCallable, Category = "Grid Management")
bool PlaceUnitOnTile(AUnitCharacter* UnitToPlace, FIntPoint GridCoordinates);

UFUNCTION(BlueprintCallable, Category = "Grid Management")
bool MoveUnitToTile(AUnitCharacter* UnitToMove, FIntPoint NewCoordinates);

UFUNCTION(BlueprintCallable, Category = "Grid Management")
void ClearTile(FIntPoint GridCoordinates);

These functions will update the FHexTileData array (setting/clearing OccupyingUnit) and update the AUnitCharacter's actual world position to align with the center of the target hex tile. Validation (e.g., is the tile occupied? is it on the player's side? does the player own the unit?) will be essential within these functions. The ATile::SetUnit method from the forum example demonstrates a similar concept of associating a unit with a tile.16
D. Querying Grid Cells and Tile InformationOther game systems will need to query the grid for information. The AHexGridManager should expose an API for this:
AUnitCharacter* GetUnitAtCoordinates(FIntPoint Coords) const;
bool IsTileOccupied(FIntPoint Coords) const;
bool IsTileValid(FIntPoint Coords) const; (Checks if coordinates are within grid bounds)
TArray<FHexTileData> GetNeighbors(FIntPoint Coords) const;
FVector GetWorldPositionForCoordinates(FIntPoint Coords) const;
FIntPoint GetCoordinatesForWorldPosition(FVector WorldPos) const;
The C++ examples in the ATileMap class from the forum discussion provide excellent starting points for functions like GetTile, GetUnit, and GetNeighbourIndex.7 The hexagonal math from Red Blob Games 15 will be vital for implementing GetNeighbors accurately. A GitHub repository, HexagonGridUE5, also illustrates a C++/Blueprint balanced approach for hex actors and grid management.17The grid system serves as a foundational data layer. Its API design and efficiency will directly influence the implementation complexity and performance of unit management, AI (for targeting), ability systems (for area-of-effect spells or range checks), and synergy calculations. A clean, well-documented C++ API for the AHexGridManager is therefore of high importance, encapsulating grid-specific logic and providing straightforward access for other game modules. For instance, combat logic will heavily rely on querying unit positions to determine valid attack targets and calculate distances, while the synergy system will need to iterate over all units on a player's side of the board to activate trait bonuses.IV. Units: Champions of the Arena (C++)Units, or champions, are the core actors in an auto-battler. Their attributes, abilities, and interactions define the gameplay.A. Base C++ Class for Units (AUnitCharacter)A base C++ class, AUnitCharacter, will serve as the parent for all playable units.
Inheritance: This class should inherit from ACharacter or APawn. ACharacter provides built-in support for skeletal meshes and a UCharacterMovementComponent, which might be useful if units have complex movement animations, even if they are mostly stationary during combat.6 For TFT units that typically only "walk" to their initial combat positions or to an attack target, a simpler APawn setup with manual position updates or a very basic movement component could also suffice and might be slightly more lightweight. Given the potential for future features or more dynamic movement during special abilities, ACharacter is often a safer, more extensible choice.
Essential Components:

USkeletalMeshComponent: For the unit's visual representation.
UAbilitySystemComponent (ASC): If using GAS, this component will be added to manage attributes and abilities.
Custom components: For any other specialized logic, e.g., a UUnitInteractionComponent if units have complex non-combat interactions.


Core C++ Properties:

FName UnitDataID;: An identifier used to look up the unit's base data from a Data Table.
int32 StarLevel;: Current star level of the unit (1, 2, or 3).
TArray<FName> EquippedItemIDs;: Stores IDs of items equipped to this unit.
If not using GAS for attributes, a USTRUCT member like FUnitStats CurrentStats;.


Discussions on character class systems often suggest using Data Assets or Data Tables to define character archetypes and their base information, which aligns with the UnitDataID approach.21B. Defining Core Unit AttributesUnit attributes (Health, Mana, Attack Damage, etc.) can be managed in two primary ways:

Using Gameplay Ability System (GAS): This is the recommended approach for a game with complex attribute interactions and status effects.

Create a UUnitAttributeSet class inheriting from UAttributeSet.3
Inside UUnitAttributeSet.h, define attributes as FGameplayAttributeData properties:
C++// In UnitAttributeSet.h
UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
FGameplayAttributeData Health;
ATTRIBUTE_ACCESSORS(UUnitAttributeSet, Health)

UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
FGameplayAttributeData MaxHealth;
ATTRIBUTE_ACCESSORS(UUnitAttributeSet, MaxHealth)

UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)
FGameplayAttributeData Mana;
ATTRIBUTE_ACCESSORS(UUnitAttributeSet, Mana)
//... other attributes like AttackDamage, AbilityPower, AttackSpeed, Armor, MagicResistance


The ATTRIBUTE_ACCESSORS macro generates getter/setter helper functions. ReplicatedUsing specifies an OnRep function to handle client-side updates when the attribute changes.
The AUnitCharacter will own an instance of this UUnitAttributeSet, typically added in its constructor if the ASC is also on the Character, or the PlayerState's ASC would own it if attributes are tied to the player level more directly for some global stats. For unit-specific stats like Health, Attack Damage, it's common for the unit's ASC to own the set. Tutorials and best practices for GAS provide extensive details on setup and usage.3



Custom C++ Structs/Variables:

Define an FUnitStats USTRUCT containing all relevant stats (e.g., float Health, MaxHealth, Mana;).
The AUnitCharacter would have an instance of FUnitStats.
All modifications to stats would be handled by custom C++ functions within AUnitCharacter or related systems. This approach is simpler to set up initially but requires significantly more manual coding for status effects, buffs, debuffs, and abilities that interact with these stats.


Given the nature of TFT, where units have diverse abilities and items frequently modify stats or apply complex effects, GAS provides a much more robust and scalable framework. The initial learning curve for GAS is steeper, but its features for managing attribute modifications via GameplayEffects, handling ability costs and cooldowns, and replicating state for potential multiplayer are highly beneficial. TFT units have numerous stats that are constantly influenced by items and trait synergies. GameplayEffects in GAS are specifically designed to handle these modifications (buffs, debuffs, temporary changes, permanent alterations) in a structured way.3 Furthermore, unit abilities often have mana costs and cooldowns, and directly interact with or scale off attributes; GAS GameplayAbilities provide built-in mechanisms for these aspects. This significantly reduces the amount of boilerplate C++ code that would otherwise be needed to implement such complex interactions manually.C. Managing Unit Data with Data TablesTo define the base properties of each unique unit type, Data Tables are an excellent choice.
Struct Definition: Create a C++ struct, FUnitBaseData, inheriting from FTableRowBase.23
C++// In a new header file, e.g., UnitData.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h" // For FGameplayTag
#include "UnitData.generated.h"

USTRUCT(BlueprintType)
struct FUnitBaseData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    int32 Cost; // Gold cost

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset; // Using TSoftObjectPtr for deferred loading

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    TSoftObjectPtr<UTexture2D> PortraitTexture;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseMana; // Starting Mana

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float MaxMana; // Mana required to cast ability

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseAttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseAttackSpeed; // Attacks per second

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    int32 AttackRange; // In hexes

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseArmor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    float BaseMagicResist;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    TSubclassOf<UGameplayAbility> UnitAbilityClass; // The ability this unit can cast

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UnitData")
    FGameplayTagContainer TraitTags; // GameplayTags representing unit's origins/classes
};


Data Table Asset: In the Unreal Editor, create a new Data Table asset and select FUnitBaseData as its row structure. Populate this table with data for each champion (e.g., Name: "Garen", Cost: 1, BaseHealth: 600, TraitTags: { "Noble", "Knight" }).
Initialization: The AUnitCharacter will have an initialization function:
C++// In AUnitCharacter.h
void InitializeFromDataTable(FName InUnitDataID, int32 InStarLevel, UDataTable* UnitDataTable);

// In AUnitCharacter.cpp
void AUnitCharacter::InitializeFromDataTable(FName InUnitDataID, int32 InStarLevel, UDataTable* UnitDataTable)
{
    if (!UnitDataTable) return;

    static const FString ContextString(TEXT("Unit Base Data Lookup"));
    FUnitBaseData* Row = UnitDataTable->FindRow<FUnitBaseData>(InUnitDataID, ContextString);

    if (Row)
    {
        this->UnitDataID = InUnitDataID;
        this->StarLevel = InStarLevel;
        // Load SkeletalMesh, Portrait, etc.
        // Initialize attributes in UUnitAttributeSet using Row data and StarLevel multipliers
        // Example for Health (assuming ASC and AttributeSet are valid):
        // float ActualMaxHealth = Row->BaseHealth * GetStarLevelMultiplier(InStarLevel);
        // AbilitySystemComponent->ApplyModToAttribute(UUnitAttributeSet::GetMaxHealthAttribute(), EGameplayModOp::Override, ActualMaxHealth);
        // AbilitySystemComponent->ApplyModToAttribute(UUnitAttributeSet::GetHealthAttribute(), EGameplayModOp::Override, ActualMaxHealth);
        // Grant abilities:
        // if (Row->UnitAbilityClass && AbilitySystemComponent)
        // {
        //     FGameplayAbilitySpec AbilitySpec(Row->UnitAbilityClass, 1, INDEX_NONE, this);
        //     AbilitySystemComponent->GiveAbility(AbilitySpec);
        // }
        // Store TraitTags, etc.
    }
}

The GetStarLevelMultiplier would be a helper function returning appropriate multipliers for stats based on star level (e.g., 1.0 for 1-star, 1.8 for 2-star, 3.24 for 3-star, these are typical TFT values). Using Data Tables as shown in tutorials 23 and the C++ example for weapon stats 25 provides a flexible way to manage and balance unit data.
D. Implementing Unit Abilities (Using GAS)Each unit's special ability will be implemented as a C++ class deriving from UGameplayAbility.3
Ability Class:
C++// Example: GarenSpinAbility.h
UCLASS()
class TFTCLONE_API UGarenSpinAbility : public UGameplayAbility
{
    GENERATED_BODY()
public:
    UGarenSpinAbility();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    // Define costs, cooldowns, targeting logic, and effects (e.g., apply GameplayEffect for damage)
};


Activation: Abilities are typically activated when a unit's Mana attribute reaches its MaxMana. The UAbilitySystemComponent on AUnitCharacter will be responsible for granting this ability (usually during initialization from the Data Table) and attempting to activate it.
Effects: The ActivateAbility method will contain the logic for the ability's effects, such as dealing area damage, applying crowd control, or buffing allies. This is often achieved by applying other GameplayEffects to targets.
The specifics of an ability (damage values, range, duration, scaling with stats like Ability Power) can be made configurable. Instead of hardcoding these values directly into the C++ UGameplayAbility class, they can be defined as UPROPERTY members that are set in a Blueprint child of the C++ ability class, or even better, read from a Data Table row specific to that ability. This approach greatly aids in game balancing, as designers can tweak ability parameters without requiring C++ recompilation. For instance, an ability's BaseDamage and AbilityPowerScalingFactor could be properties on the UGameplayAbility subclass, initialized from data when the ability is granted or activated.E. Unit Tier System (Star Levels)The core mechanic of upgrading units by combining three identical copies needs to be implemented.
Detection: Logic, likely within a player-owned component (e.g., UPlayerBenchComponent or UPlayerTeamManagerComponent) or the ATFTPlayerController, needs to monitor the player's collection of units (both on the board and on the bench). When a player acquires a third identical unit (same UnitDataID and StarLevel), the upgrade should trigger.
Process:

Identify the three identical units.
Remove the two "sacrificed" units from the game (destroy actors, update data structures).
Upgrade the remaining unit (or spawn a new one if preferred):

Increment its StarLevel.
Re-initialize its stats using InitializeFromDataTable with the new star level to apply stat multipliers.
Update its visual appearance if star levels have distinct models or VFX.




This system requires careful management of unit instances and their data. The ATFTPlayerState might hold arrays for units on the bench and references to units on the board managed by AHexGridManager.
V. The Economy: Gold, Shop, and Experience (C++)A robust economy system is central to the strategic layer of an auto-battler. Players manage gold to buy units and experience, with income influenced by savings and performance.A. Managing Player ResourcesPlayer-specific resources like gold, experience, and health will be managed primarily within the ATFTPlayerState class, as this class is designed to hold replicated state information for each player.
Gold:

A replicated UPROPERTY in ATFTPlayerState.h:
C++UPROPERTY(ReplicatedUsing = OnRep_Gold, BlueprintReadOnly, Category = "Economy")
int32 Gold;


Functions in ATFTPlayerState.cpp:

void AddGold(int32 Amount);
bool SpendGold(int32 Amount); (returns true if successful)
bool CanAfford(int32 Amount) const;


The OnRep_Gold function will be called on clients when the Gold value changes, allowing UI updates. Example C++ currency systems can be found in tutorials and plugins.30


Experience (XP) and Level:

Replicated UPROPERTYs in ATFTPlayerState.h:
C++UPROPERTY(ReplicatedUsing = OnRep_CurrentXP, BlueprintReadOnly, Category = "Economy")
int32 CurrentXP;

UPROPERTY(ReplicatedUsing = OnRep_CurrentLevel, BlueprintReadOnly, Category = "Economy")
int32 CurrentLevel;

UPROPERTY(Replicated, BlueprintReadOnly, Category = "Economy")
int32 MaxUnitsOnBoard; // Determined by CurrentLevel


Functions in ATFTPlayerState.cpp:

void AddXP(int32 Amount); (This function will also call CheckForLevelUp())
int32 GetXPToNextLevel() const;
void CheckForLevelUp(); (Compares CurrentXP to predefined thresholds)




Player Health:

A replicated UPROPERTY in ATFTPlayerState.h:
C++UPROPERTY(ReplicatedUsing = OnRep_PlayerHealth, BlueprintReadOnly, Category = "Combat")
int32 PlayerHealth;


Functions like void TakeDamage(int32 Amount);


Interest Calculation: This logic typically resides in ATFTGameModeBase. At the end of each round (e.g., during the transition from Combat to Preparation phase), the GameMode will iterate through each ATFTPlayerState:

Read the player's current Gold.
Calculate interest: +1 gold for every 10 gold held, capped at a certain amount (e.g., +5 gold).
Call PlayerState->AddGold(InterestAmount);.


Streak Bonuses: Also managed by ATFTGameModeBase. Each ATFTPlayerState might need to store its current win/loss streak count.

After each combat round, the GameMode updates the streak for each player.
Based on the streak length (e.g., 2-3 wins, 4 wins, 5+ wins), award bonus gold by calling PlayerState->AddGold(StreakBonusAmount);.


B. Implementing the Unit ShopThe unit shop is a dynamic system where players purchase champions. This can be managed by a UActorComponent, say UShopManagerComponent, attached to the ATFTPlayerController or ATFTPlayerState. The ATFTPlayerState is often preferred if shop state (like locked status or current offerings if they were to persist slightly) needs to be known by the server for that player.
Unit Pool Management:

A central, game-wide unit pool needs to be defined. This could be managed by ATFTGameStateBase to ensure all players draw from the same limited supply (as in TFT).
TMap<FName, int32> SharedUnitPoolCounts; // UnitID to remaining count
When a unit is bought, its count in SharedUnitPoolCounts decreases. When sold or a player is eliminated, their units return to this pool.


Shop Slots and Refresh Logic:

The UShopManagerComponent will have an array representing the current units offered:
C++// In ShopManagerComponent.h
UPROPERTY(ReplicatedUsing = OnRep_CurrentShopUnits, BlueprintReadOnly, Category = "Shop")
TArray<FName> CurrentShopUnits; // Stores UnitDataIDs of units in shop

UFUNCTION()
void OnRep_CurrentShopUnits(); // For UI updates on client


void Server_RefreshShop(bool bIsFreeReroll);: This function, callable by the client but executed on the server, is the core of the shop.

If not a free reroll, deduct reroll cost from player's gold (via ATFTPlayerState).
Clear CurrentShopUnits.
For each shop slot (typically 5):

Determine the probability of rolling units of different tiers (costs) based on the player's CurrentLevel (from ATFTPlayerState). This requires a data structure, perhaps a UDataAsset or a TMap<int32, FShopTierProbabilities> in C++, where FShopTierProbabilities is a struct holding percentages for each unit cost tier (e.g., Tier 1: 40%, Tier 2: 30%, etc., at Player Level X). TFT's shop odds are a critical balancing element and change dynamically with player level. A data-driven approach for these probabilities is essential for flexible balancing, allowing designers to adjust odds without C++ recompilation.
Randomly select a unit tier based on these probabilities.
Randomly select an available unit of that tier from the SharedUnitPoolCounts (ensure count > 0).
Add the selected unit's UnitDataID to CurrentShopUnits.


The OnRep_CurrentShopUnits function will trigger UI updates on the client.




Buying Units:

UFUNCTION(Server, Reliable) void Server_BuyUnit(FName UnitID, int32 ShopSlotIndex);

Called by the client when a shop card is clicked.
Server validates: Does the unit exist in CurrentShopUnits at ShopSlotIndex? Can the player afford it (check ATFTPlayerState::Gold against unit cost from FUnitBaseData)? Is there space on the player's bench?
If valid:

ATFTPlayerState::SpendGold().
Decrement count of UnitID in SharedUnitPoolCounts.
Add the new unit to the player's bench (managed by ATFTPlayerState or a dedicated bench component). This might involve spawning an AUnitCharacter instance.
Mark the unit in CurrentShopUnits as sold (e.g., replace with NAME_None or remove) or clear the slot to prevent re-purchase until next refresh.
Trigger UI updates.




Tutorials on general inventory and shop systems provide conceptual C++ examples, though TFT's specific auto-refreshing, level-dependent shop requires custom logic.33


Selling Units:

UFUNCTION(Server, Reliable) void Server_SellUnit(AUnitCharacter* UnitToSell);

Client indicates which unit (on board or bench) to sell.
Server validates ownership.
ATFTPlayerState::AddGold() (unit's cost, or a fraction thereof).
Remove the AUnitCharacter actor from the game.
Return the unit to the SharedUnitPoolCounts by incrementing its count.
Trigger UI updates.




Buying Experience:

UFUNCTION(Server, Reliable) void Server_BuyXP();

Client requests to buy XP.
Server validates: Can player afford XP cost (e.g., 4 gold)?
If valid:

ATFTPlayerState::SpendGold(XP_COST);
ATFTPlayerState::AddXP(XP_AMOUNT); (which internally checks for level up).
Trigger UI updates.






C. Player Leveling System (in ATFTPlayerState)The ATFTPlayerState will manage player levels and the XP required for them.
XP Thresholds: A TArray<int32> XPToNextLevelPerLevel; can define the total XP needed to reach each level (e.g., Level 1: 0 XP, Level 2: 2 XP, Level 3: 6 XP, etc.).
CheckForLevelUp() function:
C++// In ATFTPlayerState.cpp
void ATFTPlayerState::CheckForLevelUp()
{
    if (CurrentLevel >= MaxPlayerLevel) return; // MaxPlayerLevel defined elsewhere

    // XPToNextLevelPerLevel[CurrentLevel] would be XP needed to reach (CurrentLevel + 1)
    // Ensure array is 0-indexed matching levels, or adjust access.
    // Example: XPToNextLevelPerLevel = XP for Lvl 1, XPToNextLevelPerLevel = XP for Lvl 2
    while (CurrentLevel < MaxPlayerLevel && CurrentXP >= GetXPForLevel(CurrentLevel + 1))
    {
        CurrentLevel++;
        OnLevelUp(); // Call a function to handle level-up consequences
    }
    // Force OnRep functions if values changed
    FORCE_REP_UPDATE(CurrentXP);
    FORCE_REP_UPDATE(CurrentLevel);
}

void ATFTPlayerState::OnLevelUp()
{
    // Update MaxUnitsOnBoard based on new CurrentLevel
    // MaxUnitsOnBoard = CalculateMaxUnitsForLevel(CurrentLevel);
    // Potentially notify other systems (e.g., shop manager about new shop odds)
    // FORCE_REP_UPDATE(MaxUnitsOnBoard);
}

int32 ATFTPlayerState::GetXPForLevel(int32 TargetLevel) const
{
    // Assuming XPToNextLevelPerLevel stores cumulative XP needed for each level
    // or XP needed from previous level. Adjust logic accordingly.
    // Example: if XPToNextLevelPerLevel = {0, 2, 4, 10, 20, 36, 56, 80, 100} for levels 1-9
    if (TargetLevel > 0 && TargetLevel <= XPToNextLevelPerLevel.Num())
    {
        return XPToNextLevelPerLevel;
    }
    return MAX_int32; // Or some other large number if max level
}

The OnLevelUp() function is critical for updating game state based on the new level, such as increasing the MaxUnitsOnBoard which dictates how many units the player can field.
VI. Combat: The Auto Battle (C++)The heart of an auto-battler is the automated combat phase where units execute their behaviors.A. Game Phase ManagementAs outlined in Section II.C, a custom game phase system is essential.
Enum Definition:
C++// In a shared header file, e.g., TFTTypes.h
UENUM(BlueprintType)
enum class ETFTGamePhase : uint8
{
    Preparation     UMETA(DisplayName = "Preparation"),
    Combat          UMETA(DisplayName = "Combat"),
    PvERound        UMETA(DisplayName = "PvE Round"), // Could be a sub-state of Combat
    Carousel        UMETA(DisplayName = "Carousel"),
    RoundEnd        UMETA(DisplayName = "Round End"),
    GameOver        UMETA(DisplayName = "Game Over")
};


State Replication: ATFTGameStateBase will have a replicated UPROPERTY:
C++// In ATFTGameStateBase.h
UPROPERTY(ReplicatedUsing = OnRep_CurrentGamePhase, BlueprintReadOnly, Category = "Game Phase")
ETFTGamePhase CurrentGamePhase;

UFUNCTION()
void OnRep_CurrentGamePhase();

The OnRep_CurrentGamePhase function allows clients to react to phase changes, primarily for updating UI or client-side visual logic.
Phase Transitions: ATFTGameModeBase will orchestrate transitions between these phases. For example:
C++// In ATFTGameModeBase.h
void StartPreparationPhase();
void StartCombatPhase();
void EndCombatPhase(bool bPlayerWon); // Parameter indicates if local player won this round
//... other phase transition functions

FTimerHandle PhaseTimerHandle; // To manage duration of phases like Preparation

// In ATFTGameModeBase.cpp
void ATFTGameModeBase::StartPreparationPhase()
{
    if (ATFTGameStateBase* TFTGameState = GetGameState<ATFTGameStateBase>())
    {
        TFTGameState->SetCurrentGamePhase(ETFTGamePhase::Preparation); // This setter should handle replication
    }
    // Initialize shop, grant round gold/interest, etc.
    // Set a timer for the duration of the preparation phase
    // GetWorldTimerManager().SetTimer(PhaseTimerHandle, this, &ATFTGameModeBase::StartCombatPhase, PreparationPhaseDuration, false);
}

The engine's built-in match states 9 can serve as a conceptual reference, but a custom enum like ETFTGamePhase offers more direct mapping to TFT's specific loop. Blueprint logic for turn management in other game types can also offer inspiration for structuring phase transitions.39
B. Automated Combat LogicOnce StartCombatPhase() is called, units engage automatically.

Unit State Machine (Recommended): While optional for a very simple implementation, a state machine for each AUnitCharacter can manage its behavior more cleanly (e.g., states like Idle, MovingToTarget, Attacking, CastingAbility, Dead). A C++ state manager component could be created for this.40


Target Selection: Each AUnitCharacter (or an attached UUnitAIComponent) needs logic to find and select targets.

AUnitCharacter* FindTarget();
This function will typically:

Get a list of all enemy units currently on the board (from AHexGridManager or ATFTGameStateBase).
Filter by attack range (considering unit's AttackRange stat).
Prioritize (e.g., closest unit, lowest health percentage unit, random). TFT units usually attack the closest target within range.
Store the chosen target: TWeakObjectPtr<AUnitCharacter> CurrentAttackTarget;.


This logic should be re-evaluated if CurrentAttackTarget dies or moves out of range. The Gameplay Targeting System 41 or AI Perception system could be used for more advanced targeting, but simple distance checks and iteration are often sufficient for basic auto-battler targeting. AI controller and behavior tree examples 42 show more complex AI decision-making that could be adapted.



Attack Execution:

Managed by a timer within AUnitCharacter, firing based on its AttackSpeed attribute.
C++// In AUnitCharacter.h
FTimerHandle AttackTimerHandle;
void PerformAttack();

// In AUnitCharacter.cpp, when combat starts or target acquired:
// float AttackInterval = 1.0f / CurrentStats.AttackSpeed;
// GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AUnitCharacter::PerformAttack, AttackInterval, true);


PerformAttack():

If CurrentAttackTarget is valid and in range:

Trigger attack animation montage.
For ranged units, spawn a projectile actor or perform an instant line trace. For melee, ensure proximity.
Calculate and apply damage (see below).


Else (no valid target or target out of range):

Attempt to FindTarget(). If a new target is found, the unit might need to move towards it before attacking (simple SetActorLocation over time or using UCharacterMovementComponent if available).




Attack animation and damage application examples can be found in various combat tutorials.44



Damage Calculation:

Using GAS: When an attack hits, the attacker's AUnitCharacter applies a UGameplayEffect to the CurrentAttackTarget.

The GE should have an ExecutionCalculation class (UGameplayEffectExecutionCalculation).
This C++ class overrides Execute_Implementation to calculate damage based on attacker's AttackDamage (or AbilityPower for spells) and target's Armor (or MagicResist). Standard damage formulas like ActualDamage = RawDamage * (100 / (100 + Resistance)) can be implemented here.
The execution then modifies the target's Health attribute.
The GAS documentation and tutorials are invaluable for this.3


Custom System: If not using GAS, PerformAttack would directly fetch the attacker's damage stat and target's relevant resistance stat, calculate damage, and call a TakeDamage(float Amount) function on the target AUnitCharacter.



Mana Generation:

Units in TFT gain mana primarily by attacking and by taking damage.
On Attacking: After a successful attack in PerformAttack(), add a fixed amount of mana or mana based on damage dealt.
On Taking Damage: In the TakeDamage function (or the GAS equivalent where health is reduced), the unit taking damage gains mana.
If using GAS, these could be self-applied GameplayEffects that modify the Mana attribute, triggered by gameplay events like "OnSuccessfulAttack" or "OnDamageTaken."



Ability Casting:

Continuously check if a unit's Mana attribute has reached its MaxMana. This can be done in the UUnitAttributeSet::PostAttributeChange when Mana is modified, or periodically.
When mana is full:

If using GAS, call AbilitySystemComponent->TryActivateAbilityByHandle(UnitAbilityHandle) or TryActivateAbilityByClass(UnitAbilityClass). The UnitAbilityHandle or UnitAbilityClass would have been set during unit initialization.
The UGameplayAbility class itself then handles its targeting, effects, and mana consumption (setting Mana back to 0 or a specified value).


GAS tutorials cover ability activation in detail.3



Unit Death Handling:

In AUnitCharacter::TakeDamage (or its GAS equivalent in UUnitAttributeSet when Health is modified):

If Health drops to 0 or below:

Mark the unit as dead (e.g., set a boolean bIsDead = true;).
Stop all actions (timers, movement, further attacks/ability casting).
Play death animation and visual effects.
Disable collision or remove the unit actor from the grid data in AHexGridManager.
After a short delay (for animation), Destroy() the actor or return it to an object pool.
Notify ATFTGameModeBase that a unit has died, so it can check if the combat round has ended (e.g., all units of one player are dead). A simple death screen example exists.54





Combat logic can benefit greatly from an event-driven architecture. For example, when an attack lands, an event OnAttackLanded(AActor* Target, float DamageDealt) could be broadcast. Mana generation systems or items could subscribe to this event. Similarly, an OnDamageTaken(AActor* DamageCauser, float DamageTaken) event allows for reactive mechanics. This modularity is easier to manage and extend than deeply intertwined conditional logic. GAS itself is heavily event-driven, utilizing Gameplay Tags and Gameplay Events for communication between abilities and effects.

C. Round ResolutionManaged by ATFTGameModeBase:
Detection: When all units on one player's side (or all PvE units) are dead, the combat phase ends.
Outcome:

If the local player lost, their ATFTPlayerState::PlayerHealth is reduced. The amount of damage can depend on the number and tier of surviving enemy units.
Award base gold for the round to the player.
Update win/loss streaks and award streak gold.
Calculate and award interest gold.


Transition: Call the appropriate function to transition to the next game phase (e.g., StartRoundEndPhase(), then StartPreparationPhase() for the next PvP round, or StartCarouselPhase() if it's a carousel round).
VII. Items and Synergies: Strategic Depth (C++)Items and synergies (also known as traits, origins, or classes) add significant strategic depth to auto-battlers by modifying unit stats and behaviors.A. Item SystemItems in TFT are formed from components and provide stat bonuses or unique effects.

Data Representation: A USTRUCT FItemData inheriting from FTableRowBase will define item properties. This struct will be used with a UDataTable for managing all items in the game.23
C++// In ItemData.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h" // For special effect tags
#include "GameplayAbilitySpec.h" // For TSubclassOf<UGameplayAbility>
// Forward declare attribute set if used for stat bonuses
// class UUnitAttributeSet; 

#include "ItemData.generated.h"

// Enum to define stat types for TMap, if not directly using FGameplayAttribute
UENUM(BlueprintType)
enum class EStatType : uint8
{
    Health, MaxHealth, Mana, AttackDamage, AbilityPower, AttackSpeed, Armor, MagicResist, CritChance, CritDamage
    //... add other stats as needed
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
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    bool bIsComponent; // Is this a base component or a combined item?

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (EditCondition = "!bIsComponent"))
    FName Component1_ID; // Row name of the first component in the DataTable

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (EditCondition = "!bIsComponent"))
    FName Component2_ID; // Row name of the second component

    // Option 1: Direct stat bonuses using a TMap
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    TMap<EStatType, float> StatBonuses;

    // Option 2: If using GAS, define GameplayEffects to apply stats
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    TSubclassOf<UGameplayEffect> StatBonusEffect; // A GE that applies the item's stat bonuses

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    TSubclassOf<UGameplayAbility> GrantedAbilityClass; // An ability this item grants

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    FGameplayTag SpecialEffectTag; // A tag to identify unique passive effects handled by code/GAS
};

A UDataTable created in the editor, using FItemData as its row structure, will store all item definitions.


Item Combination:

Logic to combine two component items into a completed item. This typically happens when a unit is holding two components that form a valid recipe. This logic could reside in an inventory-like component on the AUnitCharacter or a static utility library.
A TMap<FUnorderedPair<FName, FName>, FName> CombinationRecipes; could store component pairs and their resulting combined item ID. FUnorderedPair would be a custom struct to ensure (CompA, CompB) matches (CompB, CompA).
When a second component is added to a unit already holding one, check this map. If a recipe exists, remove the two components and equip the combined item.
Various inventory system examples provide C++ concepts for item management.55 Item combination logic itself is quite specific to TFT's drag-and-drop onto units.



Equipping Items to Units:

AUnitCharacter will have a mechanism to hold equipped items, e.g., TArray<FName> EquippedItemIDs; (max 3 in TFT).
void EquipItem(FName ItemID);

Add ItemID to EquippedItemIDs.
Fetch FItemData from the item Data Table.
Apply stat bonuses:

If using GAS and StatBonusEffect, apply this GameplayEffect to the unit's ASC.
If using TMap<EStatType, float>, iterate and modify the unit's attributes directly (or through its ASC).


Grant abilities: If GrantedAbilityClass is valid, use AbilitySystemComponent->GiveAbility().
Add SpecialEffectTag to the unit's ASC if applicable.


void UnequipItem(FName ItemID);

Remove ItemID from EquippedItemIDs.
Remove stat bonuses (remove the applied GameplayEffect or revert direct stat modifications).
Remove granted abilities (AbilitySystemComponent->ClearAbility()).
Remove SpecialEffectTag.


Tutorials on equipping items and modifying stats provide foundational concepts.59

Complex item effects, such as "every third attack deals bonus magic damage" or "on taking damage, heal for X% of damage taken," are best implemented using GAS. These can be passive GameplayEffects that are always active while the item is equipped, or GameplayAbilities granted by the item. For example, a "third attack bonus" could be a UGameplayAbility that listens for an "OnAttack" event (a Gameplay Tag sent via SendGameplayEventToActor), counts attacks, and triggers its effect. Simple stat bonuses are easily handled by GameplayEffect attribute modifiers. This approach leverages GAS's strengths in handling conditional, event-driven logic and managing buffs/debuffs, avoiding complex manual C++ tracking within the AUnitCharacter's core logic.3

B. Synergy System (Traits/Origins/Classes)Synergies are activated by having multiple units with the same trait on the board, granting powerful bonuses.

Data Representation:

Unit Traits: Each AUnitCharacter will store its traits as an array of FGameplayTag:
C++// In AUnitCharacter.h
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Unit Data") // Initialized from FUnitBaseData
FGameplayTagContainer TraitTags;


Synergy Definitions: A UDataAsset or another UDataTable can define the rules for each synergy. Let's use a UDataAsset for better organization:
C++// In SynergyData.h
USTRUCT(BlueprintType)
struct FSynergyBonusLevel
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 RequiredCount; // Number of units of this trait needed for this bonus level

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Description;

    // Option 1: Direct stat bonuses for the team or trait members
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<EStatType, float> StatBonusesToAllies; // Or specific to trait members

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UGameplayEffect> EffectToApplyToTraitMembers; // e.g., +AttackSpeed GE

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UGameplayAbility> AbilityToGrantToTraitMembers;
};

USTRUCT(BlueprintType)
struct FTraitSynergyInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TraitTag; // The trait this info is for (e.g., "Trait.Class.Knight")

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FSynergyBonusLevel> BonusTiers; // Sorted by RequiredCount
};

UCLASS()
class TFTCLONE_API UTraitSynergyDataAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synergies")
    TArray<FTraitSynergyInfo> Synergies;
};





Calculating Active Synergies: This logic should reside in a component attached to the ATFTPlayerState (e.g., USynergyManagerComponent) or be managed by ATFTPlayerController.

void UpdateActiveSynergies(const TArray<AUnitCharacter*>& UnitsOnBoard);

Initialize a TMap<FGameplayTag, int32> ActiveTraitCounts;.
Iterate through UnitsOnBoard. For each unit, iterate its TraitTags and increment counts in ActiveTraitCounts.
For each entry in ActiveTraitCounts:

Find the corresponding FTraitSynergyInfo in UTraitSynergyDataAsset.
Determine the highest FSynergyBonusLevel achieved based on RequiredCount.
Store this active bonus level (e.g., in another TMap TMap<FGameplayTag, FSynergyBonusLevel> CurrentActiveBonuses;).




This function needs to be called whenever the units on the board change (unit added, removed, or traits change if that's possible). Conceptual starting points for synergy-like systems are available 39, though a robust implementation will be custom. Gameplay Tags are a natural fit for representing traits due to their hierarchical nature and easy comparison.



Applying Synergy Bonuses:

When CurrentActiveBonuses changes, iterate through all UnitsOnBoard.
For each unit and each active synergy:

Remove Old Bonuses: If the unit was previously affected by this trait's synergy (perhaps at a different tier or the synergy is no longer active), remove any associated GameplayEffects or granted GameplayAbilities. This requires careful tracking of applied effects, which GAS handles well with FActiveGameplayEffectHandle.
Apply New Bonuses:

If EffectToApplyToTraitMembers is valid and the unit has the relevant TraitTag (or if the bonus applies to all allies), apply this GameplayEffect to the unit's ASC.
If AbilityToGrantToTraitMembers is valid, grant this ability.
Direct stat modifications (StatBonusesToAllies) would also be applied here, typically via a GameplayEffect.





The dynamic application and removal of stat changes or abilities due to synergies (and items) is a complex task. GAS excels here. When a synergy becomes active, it can apply an "Infinite" duration GameplayEffect to relevant units. If the synergy becomes inactive (e.g., a unit is sold), this GE is removed, and GAS automatically reverts the attribute modifications and removes any abilities granted by that GE. A custom C++ system would require meticulous tracking of each bonus's source and its specific modifications to ensure they are correctly applied and, more importantly, correctly reverted, which can be error-prone.

VIII. User Interface (UI): Bringing it all Together (UMG with C++)The User Interface (UI) is critical for player interaction, displaying game state, shop options, unit information, and active synergies. Unreal Motion Graphics (UMG) will be used, with C++ driving the logic and data.A. Setting up Basic UMG WidgetsCreate C++ base classes for UMG widgets to encapsulate logic, then derive Blueprint UMG widgets from these for visual design.
UPlayerHUDWidget (UUserWidget): The main HUD displaying player health, gold, level, XP, round timer, and phase.
UShopWidget (UUserWidget): Displays shop unit cards, reroll/XP buttons.
UUnitCardWidget (UUserWidget): Represents a single unit in the shop or on the bench.
UUnitDisplayWidget (UUserWidget): Shows detailed stats of a selected unit.
USynergyTrackerWidget (UUserWidget): Displays active synergies and their tiers.
These C++ classes will primarily handle data binding and interactions with game systems.63B. Binding C++ Data and Logic to UMG ElementsUMG widgets designed in Blueprint can be tightly coupled with their C++ parent classes.
Exposing Data to Blueprint: Use UPROPERTY(BlueprintReadOnly, Category = "UI") in C++ to make variables accessible in the UMG designer for binding or direct use.
Binding Widgets to C++ Pointers: Use UPROPERTY(meta = (BindWidget)) to create a C++ pointer that automatically links to a UMG element (e.g., a UTextBlock or UButton) named identically in the Blueprint UMG editor.65
C++// In UPlayerHUDWidget.h
UPROPERTY(meta = (BindWidget))
class UTextBlock* GoldText;

UPROPERTY(meta = (BindWidget))
class UTextBlock* HealthText;

In the UMG Blueprint derived from UPlayerHUDWidget, you would name your TextBlocks "GoldText" and "HealthText" respectively. These C++ pointers will then be automatically assigned.
Calling C++ from UI Events: UMG buttons can have their OnClicked events call C++ functions exposed with UFUNCTION(BlueprintCallable).
Updating UMG from C++: Once BindWidget pointers are valid (typically after NativeConstruct()), C++ can directly update UMG elements:
C++// In UPlayerHUDWidget.cpp, in a function like UpdateGoldDisplay(int32 NewGold)
if (GoldText)
{
    GoldText->SetText(FText::AsNumber(NewGold));
}


Detailed examples of C++ UMG binding and data flow are available.63C. Displaying Game Information
Player HUD (UPlayerHUDWidget):

Displays Gold, Health, Level, XP (from ATFTPlayerState).
Round Timer, Current Game Phase (from ATFTGameStateBase).
Data is typically pushed to the HUD from the ATFTPlayerController or the HUD can pull from the replicated PlayerState/GameState.


Shop Interface (UShopWidget):

Contains 5 UUnitCardWidget instances.
Buttons for Reroll, Buy XP, Lock Shop. These buttons call Server_ functions on UShopManagerComponent (via ATFTPlayerController).
When UShopManagerComponent::CurrentShopUnits is updated and replicated, UShopWidget updates its unit cards with new unit data (portrait, name, cost from FUnitBaseData). Shop UI tutorials can provide visual and interaction concepts.37


Unit Information Panel (UUnitDisplayWidget):

Shown on hover or click of a unit (on board, bench, or shop).
Displays detailed stats (from AUnitCharacter's attribute set or stat struct), star level, equipped items (names/icons from FItemData), and traits (from AUnitCharacter::TraitTags and UTraitSynergyDataAsset for icons/names).


Active Synergies Display (USynergyTrackerWidget):

Shows icons and counts for currently active synergies (e.g., "Knight (2/6)").
Data sourced from USynergyManagerComponent::CurrentActiveBonuses.


Combat Information:

Damage numbers can be implemented as small UMG widgets spawned at the location of the damaged unit. If using GAS, GameplayCues are often used for such visual feedback and can trigger UMG animations or widget creation.3


D. Updating UI from Game State ChangesUI must react to changes in the underlying game state.
Delegates: The most robust method for C++ driven UI updates.

In ATFTPlayerState, declare delegates like FOnGoldChangedSignature OnGoldChanged;.
When gold is modified, broadcast the delegate: OnGoldChanged.Broadcast(NewGoldAmount);.
In UPlayerHUDWidget::NativeConstruct(), get the ATFTPlayerState and bind a local function to this delegate: PlayerState->OnGoldChanged.AddDynamic(this, &UPlayerHUDWidget::HandleGoldChanged);.
HandleGoldChanged(int32 NewGold) then updates GoldText.


Polling/Tick: For very frequently changing data that doesn't have specific events (like a continuously decreasing round timer managed in ATFTGameStateBase), the UMG widget can get the ATFTGameStateBase in its NativeTick function and update the display. This is generally less efficient than delegates for discrete changes.
OnRep Functions: If a UMG widget has a direct reference to a replicated Actor (like ATFTPlayerState or ATFTGameStateBase), it can access replicated properties. When these properties change and their OnRep_ function is called on the client, the UI can be updated within that OnRep_ function or a function it calls. This is common for replicated state.10
The connection between C++ game logic and UMG is vital for a responsive and informative UI. Changes in player resources (ATFTPlayerState) or global game state (ATFTGameStateBase) must propagate to the UI. Using C++ delegates provides an efficient, event-driven way for UI widgets to subscribe to specific data changes, avoiding the need for constant polling in NativeTick. For replicated properties, their associated OnRep_ functions serve as a natural trigger point for UI updates when new data arrives from the server.IX. Game Loop and State Management (C++)The overall game loop orchestrates the sequence of rounds, phases, and player progression. This is primarily managed by ATFTGameModeBase on the server.A. Managing Overall Game FlowATFTGameModeBase is responsible for the high-level game structure:
Round Sequencing: Implementing the progression from one round type to another (e.g., initial PvE rounds, then alternating PvP and special rounds like Carousel, then more PvE rounds at stage changes).
Stage and Round Tracking: Maintaining variables for CurrentStage and CurrentRoundInStage.
Player Elimination: Monitoring ATFTPlayerState::PlayerHealth. If a player's health reaches zero, they are eliminated. The GameMode handles this, potentially by moving them to a spectator state or ending their participation.
Game Over Condition: When only one player (or no players in a single-player context if the player is eliminated) remains, the game ends. The GameMode declares the winner or shows a game over screen.
Core GameMode and GameState documentation outlines their roles in managing game flow.9
B. State Machine for Game PhasesA finite state machine (FSM) within ATFTGameModeBase is highly recommended for managing the distinct game phases.
State Enum: Use the ETFTGamePhase enum defined earlier (Preparation, Combat, etc.).
State Variable: ATFTGameModeBase will have a ETFTGamePhase CurrentServerPhase; variable.
State Transition Functions:
C++// In ATFTGameModeBase.h
protected:
    ETFTGamePhase CurrentServerPhase;
    void EnterPhase(ETFTGamePhase NewPhase);
    void ExitPhase(ETFTGamePhase OldPhase);
    void TransitionToPhase(ETFTGamePhase TargetPhase);

// In ATFTGameModeBase.cpp
void ATFTGameModeBase::TransitionToPhase(ETFTGamePhase TargetPhase)
{
    if (CurrentServerPhase == TargetPhase) return;

    ExitPhase(CurrentServerPhase);
    CurrentServerPhase = TargetPhase;
    EnterPhase(CurrentServerPhase);

    // Update GameState so clients are aware
    if (ATFTGameStateBase* TFTGameState = GetGameState<ATFTGameStateBase>())
    {
        TFTGameState->ServerSetCurrentGamePhase(CurrentServerPhase); // This function should mark for replication
    }
}

void ATFTGameModeBase::EnterPhase(ETFTGamePhase NewPhase)
{
    switch (NewPhase)
    {
        case ETFTGamePhase::Preparation:
            // Start preparation timer, enable shop interactions, allow unit placement
            // GetWorldTimerManager().SetTimer(PhaseTimerHandle, this, &ATFTGameModeBase::OnPreparationTimerEnd, PreparationDuration, false);
            break;
        case ETFTGamePhase::Combat:
            // Disable shop/placement, initiate combat logic for all boards
            // GetWorldTimerManager().SetTimer(PhaseTimerHandle, this, &ATFTGameModeBase::OnCombatTimerEnd, CombatDuration, false);
            break;
        //... other cases
    }
}

void ATFTGameModeBase::ExitPhase(ETFTGamePhase OldPhase)
{
    switch (OldPhase)
    {
        case ETFTGamePhase::Preparation:
            // Finalize unit placements, disable shop interactions
            break;
        case ETFTGamePhase::Combat:
            // Resolve combat, deal damage to losers, award gold
            break;
        //... other cases
    }
}


The ATFTGameStateBase::ServerSetCurrentGamePhase function would set its replicated CurrentGamePhase variable, which then triggers OnRep_CurrentGamePhase on clients for UI and other client-side logic.
The State design pattern provides a general programming model for such behavior.72 Tutorials on game phase management also exist.2
A well-defined state machine in ATFTGameModeBase is fundamental for orchestrating the intricate sequence of events within each TFT round. It ensures predictable transitions and provides a clear separation of logic for different game segments like unit preparation, automated combat, and round resolution. This structure prevents the ATFTGameModeBase from becoming a monolithic block of complex conditional statements, making the game flow easier to understand, debug, and extend. Each state (phase) can encapsulate its specific entry actions (e.g., starting timers, enabling specific player inputs), exit actions (e.g., cleaning up temporary actors, calculating round results), and any logic that needs to run periodically during that phase.C. Handling Player Input Based on Game PhaseThe ATFTPlayerController should query the current game phase from ATFTGameStateBase before processing certain inputs.
Example: During ETFTGamePhase::Combat, inputs for buying units, rerolling the shop, or moving units on the board should be disabled or ignored.
C++// In ATFTPlayerController.cpp, when handling an input action
void ATFTPlayerController::HandleBuyUnitInput()
{
    if (ATFTGameStateBase* TFTGameState = GetGameState<ATFTGameStateBase>())
    {
        if (TFTGameState->GetCurrentGamePhase() == ETFTGamePhase::Preparation)
        {
            // Proceed with buying unit logic
        }
        else
        {
            // Optionally provide feedback that action is not allowed now
        }
    }
}


X. Conclusion and Next StepsThis guide has outlined the C++ framework for building a Teamfight Tactics clone in Unreal Engine 5. By following these steps, a developer can implement the foundational systems necessary for an auto-battler experience.A. Recap of Systems BuiltThe core systems addressed include:
Project Setup and Architecture: Establishing a C++ project with a scalable structure and defining core gameplay classes (ATFTGameModeBase, ATFTGameStateBase, ATFTPlayerController, ATFTPlayerState).
Hexagonal Grid: Implementing a C++ managed grid for unit placement and battlefield awareness.
Units: Creating a base AUnitCharacter class with attributes (preferably via GAS), data-driven properties from Data Tables, abilities, and a star-upgrading system.
Economy: Managing player gold, XP, and levels, along with a dynamic unit shop featuring purchasing, selling, and rerolling mechanics.
Combat: Developing an automated combat system with target selection, attack execution, damage calculation, mana generation, ability casting, and unit death handling, all orchestrated by game phase transitions.
Items and Synergies: Designing systems for item combination, equipping items to units for stat bonuses and effects, and calculating/applying synergy bonuses based on unit traits.
User Interface: Connecting C++ game logic to UMG to display player information, shop details, unit stats, and active synergies.
Game Loop: Managing the overall flow of the game through distinct phases using a state machine approach within the GameMode.
B. Potential Areas for ExpansionThe implemented systems provide a solid base. Future development could focus on:
Networking: Adapting the systems for true multiplayer gameplay, which involves careful handling of replication and server authority for all game actions. GAS is designed with replication in mind, which simplifies this for attributes and abilities.
Advanced AI: Implementing more sophisticated AI for unit targeting (e.g., prioritizing specific enemy types, focusing low-health targets) and ability usage (e.g., optimal timing or target selection for AoE abilities).
Deeper Mechanics: Introducing more complex abilities, a wider variety of items with unique active or passive effects, and more intricate synergies with multiple tiers and conditional bonuses.
Visual and Audio Polish: Integrating high-quality 3D models, animations, visual effects for attacks and abilities, and sound effects to enhance the player experience.
Persistence and Meta-Progression: Adding systems for saving player progress, a ranking or matchmaking system (for multiplayer), or unlockable cosmetics.
Carousel Round Implementation: Fully developing the shared draft (Carousel) mechanic, including unit selection from a rotating pool and item attachment.
PvE Round Variety: Designing diverse PvE encounters with unique monsters and loot tables.
C. Final EncouragementBuilding a game of this complexity is a significant undertaking. However, by breaking it down into manageable systems and leveraging the power of Unreal Engine 5 and C++, a feature-rich auto-battler can be achieved. The foundation laid out in this guide provides the essential C++ building blocks, and with continued development and iteration, can evolve into a complete and engaging game.