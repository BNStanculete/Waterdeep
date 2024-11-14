# Copyright 2024 Bogdan Stanculete. All Rights Reserved

cmake_minimum_required(VERSION 3.11..3.29)

# =======================
# Sync all git submodules
# =======================

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules.")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/externals/jsoncpp/CMakeLists.txt")
    message(FATAL_ERROR "Some submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update the submodules and try again.")
endif()
