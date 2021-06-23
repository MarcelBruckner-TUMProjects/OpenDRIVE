cmake_minimum_required(VERSION 3.10)

########################################################################################################################
### Packages ###
########################################################################################################################

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
### TESTING ###
########################################################################################################################
add_executable(Tests
        HDMapTests.cpp
        ParsingTests.cpp
        RoadTests.cpp
        GeometryTests.cpp
        ProjectorTests.cpp
        ObjectTests.cpp
        ElevationTests.cpp
        VectorTests.cpp
        FormatterTests.cpp
        ../OpenDriveConfig.h
        )
target_link_libraries(Tests PUBLIC OpenDRIVE-lib gtest_main yaml-cpp)
target_include_directories(Tests PUBLIC tests "${PROJECT_BINARY_DIR}")

include_directories(../misc/)
add_test(AllTests Tests)
