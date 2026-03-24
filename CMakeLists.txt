cmake_minimum_required(VERSION 3.21)

project(Replay_Saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Load Geode SDK
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

# Sources
set(SOURCES
    src/main.cpp
    src/ReplayRecorder.cpp
    src/ReplaySaver.cpp
)

# 🔥 IMPORTANT: target name MUST match mod id suffix
add_library(replay_saver SHARED ${SOURCES})

# 🔥 Correct syntax for your SDK
setup_geode_mod(replay_saver)
