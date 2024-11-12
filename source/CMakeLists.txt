# Copyright Bogdan Stanculete 2024. All Rights Reserved.

cmake_minimum_required(VERSION 3.29)

# ================
# Defining Targets
# ================

add_library(
    WaterdeepLogic STATIC
    GameLogic/PlayerData.cpp
    GameLogic/Initializers.cpp)

# =====================
# Including directories
# =====================

target_include_directories(
    WaterdeepLogic
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GameLogic/include)

# ====================
# Configuring compiler
# ====================

configure_compiler(
    TARGET WaterdeepLogic
    DEFINITIONS "")
