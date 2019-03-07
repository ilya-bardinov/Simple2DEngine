find_package(Doxygen 1.8.0)

if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Skip doc building.")
endif()

if(DOXYGEN_FOUND)
    # doc build only target, target is not in default build, so it must be
    # triggered explicitly
    add_custom_target(doc
        ALL
        COMMAND sphinx-build -M html . _build 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation"
        VERBATIM)

    # Where docs will be installed.
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/_build/html
        DESTINATION docs
        OPTIONAL)

    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/_build")
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/api")
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/doxyoutput")
endif()
