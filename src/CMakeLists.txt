########################################################################################################################
### Includes ###
########################################################################################################################

find_package(PROJ REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
### Library ###
########################################################################################################################

if (OPENDRIVE_1_4)
    file(GLOB opendrive_1_4 "opendrive_1_4/*.cpp")
endif ()

if (OPENDRIVE_1_6)
    file(GLOB opendrive_1_6 "opendrive_1_6/*.cpp")
endif ()

add_library(OpenDRIVE-lib
        HDMap.cpp
        Road.cpp
        Object.cpp
        OpenDriveWrapper.cpp
        Geometry.cpp
        ElevationBase.cpp
        Elevation.cpp
        SuperElevation.cpp
        HDMapFactory.cpp

        utils/Formatter.cpp
        utils/CubicPolynom.cpp
        utils/Vector.cpp
        utils/Projector.cpp
        utils/LongLatProjector.cpp

        ${opendrive_1_4}
        ${opendrive_1_6}
        )

target_include_directories(OpenDRIVE-lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        " ${PROJECT_BINARY_DIR} "
        )

if (OPENDRIVE_1_4 OR OPENDRIVE_1_6)
    set(additional_libs OpenDRIVEStandard)
endif ()
target_link_libraries(OpenDRIVE-lib
        ${additional_libs}
        ${PROJ_LIBRARIES}
        yaml-cpp
        tinyxml2
        )

