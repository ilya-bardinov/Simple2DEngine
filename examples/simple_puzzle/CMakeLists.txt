cmake_minimum_required(VERSION 3.2)

# project name
project(simple_puzzle VERSION 0.0.1 LANGUAGES CXX)

# Sources
set(
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GridNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GridElementNode.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link simple2dengine
target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
)

# Install 
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
