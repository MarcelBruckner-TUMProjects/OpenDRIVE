cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.15)

########################################################################################################################
### Packages ###
########################################################################################################################

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/misc)

########################################################################################################################
### TESTING ###
########################################################################################################################

if (OPENDRIVE_1_4)
    file(GLOB opendrive_1_4 "opendrive_1_4/*.cpp" "opendrive_1_4/*.hpp")
endif ()

if (OPENDRIVE_1_6)
    file(GLOB opendrive_1_6 "opendrive_1_6/*.cpp" "opendrive_1_6/*.hpp")
endif ()

add_executable(Tests
        ${opendrive_1_4}
        ${opendrive_1_6}
        ../OpenDriveConfig.h
        VectorTests.cpp
        OpenDriveTests.cpp
        OpenDriveTests.hpp
        ElevationTests.cpp
        FormatterTests.cpp
        GeometryTests.cpp
        ObjectTests.cpp
        ProjectorTests.cpp
        RoadTests.cpp
        LanesTests.cpp
        ArrayUtilsTests.cpp
        )

target_link_libraries(Tests PUBLIC OpenDRIVE-lib gtest_main yaml-cpp)
target_include_directories(Tests PUBLIC tests "${PROJECT_BINARY_DIR}")

add_test(AllTests Tests)
