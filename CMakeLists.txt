cmake_minimum_required(VERSION 3.21)

# ⚠️ IMPORTANT: name must match your mod id style (dash)
project(crxptos.replay-saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Load Geode SDK
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

# ✅ Your source files
set(SOURCES
    src/main.cpp
    src/ReplayRecorder.cpp
    src/ReplaySaver.cpp
)

# ✅ Build shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# ✅ THIS handles EVERYTHING (packaging, android64 folder, etc.)
setup_geode_mod(${PROJECT_NAME})
