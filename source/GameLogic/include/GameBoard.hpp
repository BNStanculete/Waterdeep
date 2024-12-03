// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <memory>

#include <GameElements.hpp>

namespace Waterdeep {

class GameBoard {
 public:
    /**
     * @brief Destructor
     */
    virtual ~GameBoard() = default;

    /**
     * @brief Returns the game board object
     * 
     * @return std::shared_ptr<GameBoard> 
     */
    static std::shared_ptr<GameBoard> GetBoardData();

 private:
    /**
     * @brief Constructor
     */
    GameBoard() = default;

    static std::shared_ptr<GameBoard> instance_;

    ActionSpaces   defaultSpaces_;
    ActionSpaces   buildingSpaces_;

    Buildings      availableBuildings_;
    Quests         avaialableQuests_;

    Quests         questDeck_;
    Intrigues      intrigueDeck_;
};

}  // namespace Waterdeep
