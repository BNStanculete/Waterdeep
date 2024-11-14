// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#include <utils/ElementCrafters.hpp>

namespace Waterdeep {

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
