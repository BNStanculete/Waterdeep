// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <memory>

#include <GameElements.hpp>

namespace Waterdeep {

class PlayerData {
 public:

    /**
     * @brief Destructor
     * 
     */
    virtual ~PlayerData() = default;

    /**
     * @brief Constructor
     * 
     * @param nrOfPlayers The total number of players in the game.
     * @param startingColor The color which starts the game
     * @param color The current player's color (AI is always Gray)
     * @param initialCoins The initial number of coins the player has
     */
    explicit PlayerData(
        const uint16_t nrOfPlayers,
        const PlayerColor startingColor,
        const PlayerColor color,
        const uint16_t initialCoins);

    // -- Prevent other forms of construction

    PlayerData(const PlayerData& other) = delete;
    PlayerData(PlayerData&& other) = delete;

    PlayerData& operator=(const PlayerData& other) = delete;
    PlayerData& operator=(PlayerData&& other) = delete;

    /**
     * @brief Executes an action and updates the player data
     * 
     * @param space The action space
     */
    void PlayAction(ActionSpace& space);

 private:
    PlayerColor     color_;

    AgentPool       playerAgents_;
    ResourcePool    playerResources_;

    Quests          activeQuests_;
    Quests          completedQuests_;
    Quests          completedPlotQuests_;

    Effects         activeEffects_;

    Intrigues       intrigues_;

    uint16_t        playerScore_;
    uint16_t        nrOfIntrigues_;

    bool            isStartingPlayer_;

    void GetReward(const RewardType type, const Reward& reward);
    bool CompleteQuest(const Quest& quest);
};

typedef std::shared_ptr<PlayerData> PlayerDataPtr;
typedef std::vector<PlayerDataPtr> Players;

// -- Bulk initializer

/**
 * @brief Creats an empty player data for all the players
 * 
 * @param colorOrders The order in which the players start
 * @return Players 
 */
Players setupPlayers(const std::vector<PlayerColor>& colorOrders);

}  // namespace Waterdeep
