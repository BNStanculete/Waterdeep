# Copyright Bogdan Stanculete 2024. All Rights Reserved.

cmake_minimum_required(VERSION 3.11..3.29)

# =========================
# Configure CMake Variables
# =========================

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# ==============
# Define Project
# ==============

project(
    WaterDeep
    
    VERSION 0.0.1
    DESCRIPTION "An algorithm  to play Lords of WaterDeep")

# =========================
# Configure Project Options
# =========================

option(BUILD_TESTS "Build UTs, CTs and System tests" ON)
option(BUILD_DOCS "Build the documentation" OFF)
option(CHECK_SUBMODULES "Check submodules during build" ON)

# ======================
# Including Dependencies
# ======================

include(SyncSubmodules)
include(ConfigureSystem)
include(ConfigureCompiler)

add_subdirectory("${PROJECT_SOURCE_DIR}/externals/jsoncpp" "externals/jsoncpp")

# ========================
# Configuring Dependencies
# ========================

set_target_properties(jsoncpp_lib PROPERTIES FOLDER externals)
get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)

# =======================
# Configuring Application
# =======================

add_subdirectory(source)
