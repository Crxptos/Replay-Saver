cmake_minimum_required(VERSION 3.21)

project(Replay_Saver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Load Geode SDK
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

# ✅ Source files (match your mod)
set(SOURCES
    src/main.cpp
    src/ReplayRecorder.cpp
    src/ReplaySaver.cpp
)

# ✅ Build shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# ✅ Setup Geode mod
setup_geode_mod(${PROJECT_NAME})
