########################################################################################################################
### YAML CPP ###
########################################################################################################################

# Download and unpack tinyxml2 at configure time
configure_file(CMakeLists.txt.in tinyxml2-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-download)
if (result)
    message(FATAL_ERROR "CMake step for tinyxml2 failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-download)
if (result)
    message(FATAL_ERROR "Build step for tinyxml2 failed: ${result}")
endif ()

# Add tinyxml2 directly to our build. This defines
# the googletest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-src
        ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-build
        EXCLUDE_FROM_ALL)
