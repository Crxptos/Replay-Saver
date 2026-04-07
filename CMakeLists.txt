cmake_minimum_required(VERSION 3.21)

project(Replay_Saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔥 MUST BE BEFORE add_subdirectory
set(GEODE_GD_VERSION 2.2081)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

set(SOURCES
    src/main.cpp
    src/ReplaySaver.cpp
    src/ReplayRecorder.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "crxptos.replay_saver")

setup_geode_mod(${PROJECT_NAME})
