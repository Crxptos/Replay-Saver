cmake_minimum_required(VERSION 3.21)

project(Replay_Saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Load Geode
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

# Sources
set(SOURCES
    src/main.cpp
    src/ReplayRecorder.cpp
    src/ReplaySaver.cpp
)

# 🔥 Create library (name matters!)
add_library(Replay_Saver SHARED ${SOURCES})

# 🔥 LINK target explicitly (THIS is the fix)
setup_geode_mod(
    TARGET Replay_Saver
    ID crxptos.replay_saver
)
