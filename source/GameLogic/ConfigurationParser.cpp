// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#include <fstream>

#include <utils/JSONParsers.hpp>
#include <utils/ElementCrafters.hpp>
#include <utils/TypeConverters.hpp>

ConfigurationParser::ConfigurationParser(const std::string& path) {
    std::ifstream fin(path);

    if (fin.good()) {
        fin >> root_;
    }
}

void ConfigurationParser::extractActionSpaces(Waterdeep::ActionSpaces* container) {
    if (root_.empty() || !root_.isMember("ActionSpaces")) {
        return;
    }

    const Json::Value& actionSpacesContainer = root_["ActionSpaces"];
    for (const Json::Value& actionSpace : actionSpacesContainer) {
        if (!actionSpace.isMember("Name")       ||
            !actionSpace.isMember("RewardType") ||
            !actionSpace.isMember("Reward")     ||
            !actionSpace.isMember("SecondaryRewardType")) {
            continue;
        }

        std::string spaceName = actionSpace["Name"].asString();

        RewardType rewardType = getRewardType(actionSpace["RewardType"].asString());
        RewardType secondaryRewardType = getRewardType(actionSpace["SecondaryRewardType"].asString());

        if (rewardType == RewardType::RESOURCE) {
            const Json::Value& rewardNode = actionSpace["Reward"];
            Waterdeep::ResourcePool pool;

            for (const std::string& key : rewardNode.getMemberNames()) {
                ResourceType resourceType = getResourceType(key);
                uint16_t resourceAmount = rewardNode[key].asUInt();

                pool[resourceType] = resourceAmount;
            }

            if (secondaryRewardType == RewardType::NONE) {
                container->push_back(Waterdeep::craftActionSpace(spaceName, pool));
            }
        }

        // TODO(Bogdan): Deal with effects
    }
}
