# Copyright Bogdan Stanculete 2024. All Rights Reserved.

cmake_minimum_required(VERSION 3.11..3.29)

# ============================
# Define system-wide variables
# ============================

set(CMAKE_PLATFORM_OS "Windows")
set(CMAKE_PLATFORM_ARCH "x64")

# =============================
# Perform necessary adjustments
# =============================

if(NOT WIN32)
    message(STATUS "Configuring for Linux distributions.")
    set(CMAKE_PLATFORM_OS "Linux")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "Changing architecture to target x86 systems.")
    set(CMAKE_PLATFORM_ARCH "x86")
endif()
