// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#include <PlayerData.hpp>

namespace Waterdeep {

PlayerData::PlayerData(
        const uint16_t nrOfPlayers,
        const PlayerColor startingColor,
        const PlayerColor color,
        const uint16_t initialCoins) :
    color_(color),
    playerAgents_(4, 4),
    playerResources_(),
    activeQuests_(),
    completedQuests_(),
    completedPlotQuests_(),
    activeEffects_(),
    intrigues_(),
    playerScore_(0),
    nrOfIntrigues_(0),
    isStartingPlayer_((startingColor == color)) {
    playerResources_[ResourceType::COIN] = initialCoins;
    if (nrOfPlayers == 2 || nrOfPlayers == 3)
        return;

    playerAgents_.first = 7 - nrOfPlayers;
    playerAgents_.second = 7 - nrOfPlayers;
}

void PlayerData::PlayAction(ActionSpace* space) {
    // Cannot perform action if player has no agents left.
    if (playerAgents_.first == 0) {
        return;
    }

    space->occupier_ = PlayerColor::NO_PLAYER;

    GetReward(space->rewardType_, space->reward_);

    if (space->secondaryRewardType_ != RewardType::NONE) {
        GetReward(space->secondaryRewardType_, space->secondaryReward_.value());
    }

    // Check if any quests can be completed.
    uint16_t index = 0;
    uint16_t completed_index = activeQuests_.size() + 1;
    for (const Quest& quest : activeQuests_) {
        if (CompleteQuest(quest)) {
            completed_index = index;
            break;
        }

        index++;
    }

    if (completed_index < activeQuests_.size()) {
        // If a quest has been completed move it accordingly
        if (activeQuests_[completed_index].isPlotQuest_) {
            completedPlotQuests_.push_back(activeQuests_[completed_index]);
        } else {
            completedQuests_.push_back(activeQuests_[completed_index]);
        }

        activeQuests_.erase(activeQuests_.begin() + completed_index);
    }
}

bool PlayerData::CompleteQuest(const Quest& quest) {
    for (const ResourceType resource : IterableResourceTypes) {
        // Ensure that the player can afford the quest
        if (playerResources_[resource] < quest.cost_.at(resource)) {
            return false;
        }
    }

    // Pay the cost
    for (const ResourceType resource : IterableResourceTypes) {
        playerResources_[resource] -= quest.cost_.at(resource);
    }

    // Get the reward
    if (quest.rewardType_ != RewardType::NONE) {
        GetReward(quest.rewardType_, quest.reward_);

        if (quest.secondaryRewardType_ != RewardType::NONE) {
            GetReward(quest.secondaryRewardType_, quest.secondaryReward_.value());
        }
    }

    playerScore_ += quest.score_;

    // TODO(BNStanculete): Check for active effects and resolve

    return true;
}

void PlayerData::GetReward(const RewardType type, const Reward& reward) {
    if (type == RewardType::RESOURCE) {
        const ResourcePool& poolReward = std::get<ResourcePool>(reward);

        for (const ResourceType resource : IterableResourceTypes) {
            playerResources_[resource] += poolReward.at(resource);
        }
    }

    // TODO(BNStanculete): IMPLEMENT EFFECT REWARDS
}

Players setupPlayers(const std::vector<PlayerColor>& colorOrders) {
    const uint16_t nrOfPlayers = static_cast<uint16_t>(colorOrders.size());
    Players playerDatas;
    uint16_t bonusCoins = 0;

    for (const PlayerColor& color : colorOrders) {
        playerDatas.push_back(std::make_shared<PlayerData>(
            nrOfPlayers, colorOrders[0], color, STARTING_COINS_DEFAULT + bonusCoins));
        bonusCoins++;
    }

    return playerDatas;
}

}  // namespace Waterdeep
