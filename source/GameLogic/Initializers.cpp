// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#include <type_traits>

#include <GameElements.hpp>

namespace Waterdeep {

// -- Begin helper functions --

template<typename ContainerType, typename RewardTypeRaw>
inline void applyReward(ContainerType& targetSpace,
                        const RewardTypeRaw& reward,
                        bool isSecondary = false) {
    
    // Ensure that the container can store rewards
    static_assert(std::is_same<ContainerType, ActionSpace>::value ||
                  std::is_same<ContainerType, Quest>::value       ||
                  (std::is_same<ContainerType, Building>::value && !isSecondary));

    targetSpace.secondaryRewardType_ = RewardType::NONE;
    targetSpace.secondaryReward_ = std::nullopt;

    if (isSecondary) {
        targetSpace.secondaryRewardType_ = (std::is_same<RewardTypeRaw, ResourcePool>::value) ?
            RewardType::RESOURCE : RewardType::EFFECT;
        targetSpace.secondaryReward_ = std::make_optional<RewardTypeRaw>(reward);

        return;
    }

    targetSpace.rewardType_ = (std::is_same<RewardTypeRaw, ResourcePool>::value) ?
        RewardType::RESOURCE : RewardType::EFFECT;
    targetSpace.reward_ = reward;
}

template<typename RewardTypeRaw1, typename RewardTypeRaw2>
inline ActionSpace craftActionSpace(const std::string& spaceName,
                                    const RewardTypeRaw1& reward,
                                    const RewardTypeRaw2& optReward) {

    // Ensure that no wrong type is applied to the template
    static_assert(std::is_same<RewardTypeRaw1, ResourcePool>::value ||
                  std::is_same<RewardTypeRaw1, Effect>::value);

    static_assert(std::is_same<RewardTypeRaw2, ResourcePool>::value ||
                  std::is_same<RewardTypeRaw2, Effect>::value);

    ActionSpace newSpace;

    newSpace.spaceName_ = spaceName;

    applyReward(newSpace, reward);
    applyReward(newSpace, optReward, true);

    return newSpace;
}

template<typename RewardTypeRaw1>
inline ActionSpace craftActionSpace(const std::string& spaceName,
                                    const RewardTypeRaw1& reward) {

    // Ensure that no wrong type is applied to the template
    static_assert(std::is_same<RewardTypeRaw1, ResourcePool>::value ||
                  std::is_same<RewardTypeRaw1, Effect>::value);

    ActionSpace newSpace;

    newSpace.spaceName_ = spaceName;
    newSpace.isOccupied_ = false;

    applyReward(newSpace, reward);

    return newSpace;
}

template<class... Resource>
inline ResourcePool craftResourcePool(Resource... resources) {
    ResourcePool pool;

    ([&] {
        pool[resources.first] = resources.second;
    } (), ...);

    return pool;
}

inline Effect craftEffect(const Modifier modifier, const uint16_t submodifier) {
    Effect newEffect;

    newEffect.first = modifier;
    newEffect.second = submodifier;

    return newEffect;
}

// -- End helper functions --

ActionSpaces setupInitialActionSpaces() {
    ActionSpaces startingSpaces;

    startingSpaces.push_back(
        craftActionSpace("Field of Triumph", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::WARRIOR, 2))));

    startingSpaces.push_back(
        craftActionSpace("The Grinning Lion Tavern", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::ROGUE, 2))));

    startingSpaces.push_back(
        craftActionSpace("The Plinth", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::PRIEST, 1))));

    startingSpaces.push_back(
        craftActionSpace("Blackstaff Tower", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::MAGE, 1))));

    startingSpaces.push_back(
        craftActionSpace("Aurora's Realms Workshop", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::COIN, 4))));

    startingSpaces.push_back(
        craftActionSpace("Castle Waterdeep",
                craftEffect(Modifier::AGENT_MOD, GET_FIRST_PLAYER),
                craftEffect(Modifier::INTRIGUE_MOD, GET_INTRIGUE)));

    startingSpaces.push_back(
        craftActionSpace("Builder's Hall",
                craftEffect(Modifier::BUILDING_MOD, BUY_BUILDING)));

    startingSpaces.push_back(
        craftActionSpace("CliffWatch Inn 1", craftResourcePool(
                std::make_pair<ResourceType, uint16_t>(ResourceType::COIN, 2)),
                craftEffect(Modifier::QUEST_MOD, GET_QUEST_SLOT)));

    startingSpaces.push_back(
        craftActionSpace("CliffWatch Inn 2",
                craftEffect(Modifier::QUEST_MOD, GET_QUEST_SLOT),
                craftEffect(Modifier::INTRIGUE_MOD, GET_INTRIGUE)));

    startingSpaces.push_back(
        craftActionSpace("CliffWatch Inn 3",
                craftEffect(Modifier::QUEST_MOD, RESET_QUESTS)));

    startingSpaces.push_back(
        craftActionSpace("Waterdeep Harbour 1",
                craftEffect(Modifier::INTRIGUE_MOD, PLAY_INTRIGUE_HARBOUR)));

    startingSpaces.push_back(
        craftActionSpace("Waterdeep Harbour 2",
                craftEffect(Modifier::INTRIGUE_MOD, PLAY_INTRIGUE_HARBOUR)));

    startingSpaces.push_back(
        craftActionSpace("Waterdeep Harbour 3",
                craftEffect(Modifier::INTRIGUE_MOD, PLAY_INTRIGUE_HARBOUR)));

    return startingSpaces;
}

}  // namespace Waterdeep
