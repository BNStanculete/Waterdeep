// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <string>
#include <type_traits>

#include <GameElements.hpp>

namespace Waterdeep {

template<typename ContainerType, typename RewardTypeRaw>
inline void applyReward(ContainerType* targetSpace,
                        const RewardTypeRaw& reward,
                        bool isSecondary = false) {
    // Ensure that the container can store rewards
    static_assert(std::is_same<ContainerType, ActionSpace>::value ||
                  std::is_same<ContainerType, Quest>::value       ||
                  (std::is_same<ContainerType, Building>::value && !isSecondary));

    targetSpace->secondaryRewardType_ = RewardType::NONE;
    targetSpace->secondaryReward_ = std::nullopt;

    if (isSecondary) {
        targetSpace->secondaryRewardType_ = (std::is_same<RewardTypeRaw, ResourcePool>::value) ?
            RewardType::RESOURCE : RewardType::EFFECT;
        targetSpace->secondaryReward_ = std::make_optional<RewardTypeRaw>(reward);

        return;
    }

    targetSpace->rewardType_ = (std::is_same<RewardTypeRaw, ResourcePool>::value) ?
        RewardType::RESOURCE : RewardType::EFFECT;
    targetSpace->reward_ = reward;
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

    applyReward(&newSpace, reward);
    applyReward(&newSpace, optReward, true);

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
    newSpace.cost_ = ResourcePool();

    applyReward(&newSpace, reward);

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

}  // namespace Waterdeep
