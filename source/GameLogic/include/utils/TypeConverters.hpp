// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <string>
#include <GameElements.hpp>

using Waterdeep::RewardType;
using Waterdeep::ResourceType;
using Waterdeep::QuestType;

constexpr RewardType getRewardType(const std::string& text) {
    if (text == "Resource") return RewardType::RESOURCE;
    if (text == "Effect") return RewardType::EFFECT;
    return RewardType::NONE;
}

constexpr ResourceType getResourceType(const std::string& text) {
    if (text == "Warrior") return ResourceType::WARRIOR;
    if (text == "Rogue") return ResourceType::ROGUE;
    if (text == "Priest") return ResourceType::PRIEST;
    if (text == "Mage") return ResourceType::MAGE;
    if (text == "Coin") return ResourceType::COIN;
    return ResourceType::ANY;
}

constexpr QuestType getQuestType(const std::string& text) {
    if (text == "Piety") return QuestType::PIETY;
    if (text == "Arcana") return QuestType::ARCANA;
    if (text == "Skullduggery") return QuestType::SKULLDUGERY;
    if (text == "Warfare") return QuestType::WARFARE;
    return QuestType::COMMERCE;
}
