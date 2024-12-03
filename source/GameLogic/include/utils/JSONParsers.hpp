// Copyright Bogdan Stanculete 2024. All Rights Reserved.

#pragma once

#include <json/json.h>

#include <string>

#include <GameElements.hpp>

class ConfigurationParser {
 public:
    /**
     * @brief Destructor
     * 
     */
    virtual ~ConfigurationParser() = default;

    /**
     * @brief Constructor
     * 
     * @param path The path to the configuration data. Defaults to
     *              'data/waterdeep.json'.
     */
    explicit ConfigurationParser(const std::string& path = "./data/waterdeep.json");

    // -- Block other forms of construction --

    ConfigurationParser(const ConfigurationParser& other) = delete;
    ConfigurationParser(ConfigurationParser&& other) = delete;

    ConfigurationParser& operator=(const ConfigurationParser& other) = delete;
    ConfigurationParser& operator=(ConfigurationParser&& other) = delete;

    // -- Methods to extract data --

    /**
     * @brief Parses the current node as an action space.
     * 
     * The function parses the current node and attempts to build an action space
     * based on the extracted details.
     * 
     * @param container The container that will store the ActionSpace
     */
    void extractActionSpaces(Waterdeep::ActionSpaces* container);

    /**
     * @brief Parses the current node as a building space.
     * 
     * The function parses the current node and attempts to build a building space
     * based on the extracted details.
     * 
     * @param container The container that will store the Building
     */
    void extractBuildings(Waterdeep::Buildings* container);

    /**
     * @brief Parses the current node as a quest.
     * 
     * The function parses the current node and attempts to build a quest
     * based on the extracted details.
     * 
     * @param container The container that will store the Quest
     */
    void extractQuests(Waterdeep::Quests* container);

    /**
     * @brief Parses the current node as an intrigue.
     * 
     * The function parses the current node and attempts to build an intrigue
     * based on the extracted details.
     * 
     * @param container The container that will store the Intrigues
     */
    void extractIntrigues(Waterdeep::Intrigues* container);

 private:
    Json::Value root_;
};
