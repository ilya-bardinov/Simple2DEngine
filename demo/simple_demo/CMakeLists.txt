cmake_minimum_required(VERSION 3.2)

# project name
project(simple_demo VERSION 0.0.1 LANGUAGES CXX)

# Sources
set(
    SOURCES
    ${simple_demo_SOURCE_DIR}/src/main.cpp
    ${simple_demo_SOURCE_DIR}/src/GameScene.cpp
    ${simple_demo_SOURCE_DIR}/src/GridNode.cpp
    ${simple_demo_SOURCE_DIR}/src/GridElementNode.cpp
)

# Executable
add_executable(simple_demo ${SOURCES})

# Link simple2dengine
target_link_libraries(
    simple_demo
    simple2dengine
)

# Install 
install(
    TARGETS simple_demo
    RUNTIME DESTINATION bin
)
