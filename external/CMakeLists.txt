include(ExternalProject)

if(BUILD_UNITTESTS)
    # We need git
    find_package(Git REQUIRED)

    #------------------------------------------------------------------------------
    # Catch - Unit test header only library
    #  * sets EXTERNAL_CATCH_INCLUDE_DIR 

    ExternalProject_Add(
        Catch
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        # For shallow git clone (without downloading whole history)
        # GIT_SHALLOW 1
        # For point at certain tag
        # GIT_TAG "v2.6.1"
        #disables auto update on every build
        UPDATE_DISCONNECTED 1
        #disable following
        CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    )
    # Update Catch target
    add_custom_target(external-Catch-update
        COMMENT "Updated Catch"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Catch/src/Catch
        COMMAND ${GIT_EXECUTABLE} pull
        DEPENDS Catch
    )
    # set include directory
    set(EXTERNAL_CATCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Catch/src/Catch/single_include/catch2" PARENT_SCOPE)

    # remove Catch directory on clean
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Catch")
endif()
