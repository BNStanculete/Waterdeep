// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#include <GameBoard.hpp>

using Waterdeep::GameBoard;

std::shared_ptr<GameBoard> GameBoard::instance_ = nullptr;
std::shared_ptr<GameBoard> GameBoard::GetBoardData() {
    if (!instance_) {
        instance_ = std::make_shared<GameBoard>(GameBoard());
    }

    return instance_;
}
