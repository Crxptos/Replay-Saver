cmake_minimum_required(VERSION 3.21)

project(Replay_Saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

set(SOURCES
    src/main.cpp
    src/ReplayRecorder.cpp
    src/ReplaySaver.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME}
    ID crxptos.replay-saver
)
