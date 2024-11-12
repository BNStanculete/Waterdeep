# Copyright Bogdan Stanculete 2024. All Rights Reserved.

cmake_minimum_required(VERSION 3.29)

# ========================
# Ensure build type is set
# ========================

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# =====================
# Define compiler macro
# =====================

function(configure_compiler)
    cmake_parse_arguments(PARSE_ARGV 0 COMPILER "" TARGET DEFINITIONS)

    message(STATUS "Configuring compiler options for ${COMPILER_TARGET}")
    if(MSVC)
        message(STATUS "Target compiler: MSVC")

        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_compile_options(
                ${COMPILER_TARGET}
                PRIVATE
                    -W4
                    -WX)
        else()

        endif()
    elseif(MINGW)
        message(STATUS "Target compiler: MinGW")

        if(CMAKE_BUILD_TYPE STREQUAL "Debug")

        else()

        endif()
    endif()

    target_compile_definitions(
        ${COMPILER_TARGET}
        PRIVATE
            ${COMPILER_DEFINITIONS}   
    )
endfunction()