########################################################################################################################
### YAML CPP ###
########################################################################################################################

# Download and unpack yaml-cpp at configure time
configure_file(CMakeLists.txt.in yaml-cpp-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-download)
if (result)
    message(FATAL_ERROR "CMake step for yaml-cpp failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-download)
if (result)
    message(FATAL_ERROR "Build step for yaml-cpp failed: ${result}")
endif ()

# Add yaml-cpp directly to our build. This defines
# the googletest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-src
        ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-build
        EXCLUDE_FROM_ALL)
