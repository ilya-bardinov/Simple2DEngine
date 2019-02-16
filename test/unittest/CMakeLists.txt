#------------------------------------------------------------------------------
# Unit tests via Catch framework
#
# For testing on the function/class level.

add_executable(unittests EXCLUDE_FROM_ALL
    testmain.cpp
)
add_dependencies(unittests Catch Simple2DEngine) # Catch is needed for unit tests, located in ../external
add_compile_options(/std:c++14 )
target_compile_definitions(unittests PRIVATE UNIT_TESTS) # add -DUNIT_TESTS define
target_include_directories(unittests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(unittests SYSTEM PRIVATE 
    ${EXTERNAL_CATCH_INCLUDE_DIR}
)
target_link_libraries(
    unittests
    Simple2DEngine
)

# convenience target for running only the unit tests
add_custom_target(unit
    #this way we can use faux data from /test dir (if we have any):
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests>
    DEPENDS unittests
)
# Verbose printing of results
add_custom_target(unitVerbose
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests> -s -a -r=compact
    DEPENDS unittests
)


