cmake_minimum_required (VERSION 3.2)

# Project setup, versioning stuff here, change when changing the version
project (simple2dengine VERSION 0.1.0)

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Project configuration ==")
message(STATUS "")

#------------------------------------------------------------------------------
# General settings

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We can use include() and find_package() for our scripts in there
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)

#------------------------------------------------------------------------------
# Enable helpfull warnings and C++14 for all files
if(MSVC)
    add_compile_options(/std:c++14 /W3 /WX )
else()
    add_compile_options(-std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic)
endif()

#------------------------------------------------------------------------------

option(BUILD_DOCS               "Build documentation."          OFF)
option(BUILD_UNITTESTS          "Enable Unittests with Catch2." OFF)
option(BUILD_DEMO               "Build demo project."           OFF)

#------------------------------------------------------------------------------

# External resources/repositories are downloaded here
add_subdirectory(external)

# Documentation
if(BUILD_DOCS)
    add_subdirectory(docs)
endif()

# Testing
if(BUILD_UNITTESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Demo project
if(BUILD_DEMO)
    add_subdirectory(demo)
endif()

# Source code
add_subdirectory(src)

#-------------------------------------------------------------------------------
# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "Build Documentation:  ${BUILD_DOCS}")
message(STATUS "Build Unit Tests:     ${BUILD_UNITTESTS}")
message(STATUS "Build Demo:           ${BUILD_DEMO}")
message(STATUS "")
