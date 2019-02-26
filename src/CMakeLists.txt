
# SFML dependencies
set(SFML_MIN_VERSION 2.5.1)
find_package(SFML COMPONENTS window system graphics audio REQUIRED)


# Sources
set(
    SOURCES
    ${simple2dengine_SOURCE_DIR}/src/engine.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/scene_manager.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/asset_manager.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/input_manager.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/loaders/loader.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/loaders/texture_loader.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/loaders/sound_loader.cpp
    ${simple2dengine_SOURCE_DIR}/src/managers/loaders/font_loader.cpp
    ${simple2dengine_SOURCE_DIR}/src/nodes/node.cpp
    ${simple2dengine_SOURCE_DIR}/src/nodes/sprite_node.cpp
    ${simple2dengine_SOURCE_DIR}/src/nodes/sound_node.cpp
    ${simple2dengine_SOURCE_DIR}/src/nodes/text_node.cpp
    ${simple2dengine_SOURCE_DIR}/src/nodes/timer_node.cpp
)

# Executable
add_library(simple2dengine STATIC ${SOURCES})

# Link SFML
target_link_libraries(
    simple2dengine 
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
)

# Headers should be visible 
target_include_directories(
    simple2dengine
    PUBLIC
        $<BUILD_INTERFACE:${simple2dengine_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install library
install(
    TARGETS simple2dengine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)

# Install headers
install(
    DIRECTORY ${simple2dengine_SOURCE_DIR}/include/simple2dengine
    DESTINATION include
)
