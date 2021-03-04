
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
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-src
        ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-build
        EXCLUDE_FROM_ALL)


########################################################################################################################
### Library ###
########################################################################################################################
find_package(PROJ)

add_subdirectory(standard)

add_library(libOpenDRIVE
        HDMap.cpp
        Road.cpp
        Object.cpp
        OpenDriveWrapper.cpp
        Geometry.cpp
        Vector.cpp
        Projector.cpp
        Elevation.cpp
        Formatter.hpp
        )

target_include_directories(libOpenDRIVE
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVE
        libOpenDRIVEStandard
        ${PROJ_LIBRARIES}
        yaml-cpp
        )

