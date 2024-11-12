// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <unordered_map>
#include <stdint.h>
#include <optional>
#include <utility>
#include <variant>
#include <string>

namespace Waterdeep {

enum ResourceType {
    WARRIOR = 0,
    ROGUE   = 1,
    PRIEST  = 2,
    MAGE    = 3,
    COIN    = 4
};

enum QuestType {
    PIETY       = 0,
    SKULLDUGERY = 1,
    WARFARE     = 2,
    ARCANA      = 3,
    COMMERCE    = 4
};

enum RewardType {
    NONE        = 0,
    RESOURCE    = 1,
    EFFECT      = 2,
};

enum Modifier {
    AGENT_MOD       = 0,
    RESOURCE_MOD    = 1,
    QUEST_MOD       = 2,
    INTRIGUE_MOD    = 3,
    PLACEMENT_MOD   = 4,
    POINTS_MOD      = 5,
    BUILDING_MOD    = 6
};

enum PlayerColor {
    RED     = 0,
    GREEN   = 1,
    YELLOW  = 2,
    BLUE    = 3,
    GRAY    = 4
};

/*
 first = Agents available
 second = Agents total
*/
typedef std::pair<uint16_t, uint16_t> AgentPool;
typedef std::unordered_map<ResourceType, uint16_t> ResourcePool;

typedef std::pair<Modifier, uint16_t> Effect;
typedef std::vector<Effect> Effects;

typedef std::variant<ResourcePool, Effect> Reward;
typedef std::optional<Reward> OptReward;

// Aliases

typedef std::pair<std::string, Effect> Intrigue;
typedef std::vector<Intrigue> Intrigues;

struct Quest {
    std::string     name_;

    QuestType       type_;
    ResourcePool    cost_;

    RewardType      rewardType_;     
    Reward          reward_;

    RewardType      secondaryRewardType_;
    OptReward       secondaryReward_;

    uint16_t        score_;

    bool            isPlotQuest_;
};

typedef std::vector<Quest> Quests;

struct ActionSpace {
    std::string     spaceName_;

    RewardType      rewardType_;
    Reward          reward_;

    RewardType      secondaryRewardType_;
    OptReward       secondaryReward_;

    bool            isOccupied_;
};

struct Building {
    std::string     buildingName_;

    ActionSpace     buildingTransition_;

    RewardType      ownerRewardType_;
    Reward          ownerReward_;

    PlayerColor     ownerColor_;

    uint16_t        buildingCost_;
    uint16_t        bonusPoints_;
};

typedef std::vector<Building> Buildings;
typedef std::vector<ActionSpace> ActionSpaces;

// -- Game constants

#define STARTING_COINS_DEFAULT 4

#define BUILDING_STACK_SIZE 15
#define BUILDING_SPACES 10
#define BUILDING_SHOP_SLOTS 3

#define QUEST_SLOTS 4

#define NR_OF_ROUNDS 8

#define WATERDEEP_HARBOUR_SLOTS 3

// -- Iterable types

static std::vector<ResourceType> IterableResourceTypes = {
    ResourceType::WARRIOR,
    ResourceType::ROGUE,
    ResourceType::MAGE,
    ResourceType::PRIEST,
    ResourceType::COIN
};

// -- Modifier actions

#define BUY_BUILDING 60

#define GET_FIRST_PLAYER 0
#define GET_NEW_AGENT 1

#define GET_INTRIGUE 30
#define PLAY_INTRIGUE_HARBOUR 31
#define PLAY_INTRIGUE_FREE 32

#define GET_QUEST_DECK 20
#define GET_QUEST_SLOT 21
#define RESET_QUESTS 23

// -- Global initializers

/**
 * @brief Initializes the starting actionSpaces
 * 
 * @return ActionSpaces 
 */
ActionSpaces setupInitialActionSpaces();

/**
 * @brief Initializes all the quests
 * 
 * @return Quests 
 */
Quests setupQuestDeck();

}  // namespace Waterdeep
