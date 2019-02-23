
# SFML dependencies
set(SFML_MIN_VERSION 2.5.1)
find_package(SFML COMPONENTS window system graphics audio REQUIRED)


# Sources
set(
    SOURCES
    ${Simple2DEngine_SOURCE_DIR}/src/engine.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/scene_manager.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/asset_manager.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/loaders/loader.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/loaders/texture_loader.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/loaders/sound_loader.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/managers/loaders/font_loader.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/nodes/node.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/nodes/sprite_node.cpp
    ${Simple2DEngine_SOURCE_DIR}/src/nodes/sound_node.cpp
)

# Executable
add_library(Simple2DEngine STATIC ${SOURCES})

# Link SFML
target_link_libraries(
    Simple2DEngine 
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
)

# Headers should be visible 
target_include_directories(
    Simple2DEngine
    PUBLIC
        $<BUILD_INTERFACE:${Simple2DEngine_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install library
install(
    TARGETS Simple2DEngine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)

# Install headers
install(
    DIRECTORY ${Simple2DEngine_SOURCE_DIR}/include/simple2dengine
    DESTINATION include
)
