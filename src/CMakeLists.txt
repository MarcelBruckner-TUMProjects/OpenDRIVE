########################################################################################################################
### Includes ###
########################################################################################################################

find_package(PROJ REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
### Library ###
########################################################################################################################

add_library(OpenDRIVE-lib
        HDMap.cpp
        Road.cpp
        Object.cpp
        OpenDriveWrapper.cpp
        Geometry.cpp
        Vector.cpp
        Projector.cpp
        ElevationBase.cpp
        Elevation.cpp
        SuperElevation.cpp
        Formatter.cpp
        ParamPoly3.cpp
        )

target_include_directories(OpenDRIVE-lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        "${PROJECT_BINARY_DIR}"
        )

target_link_libraries(OpenDRIVE-lib
        OpenDRIVEStandard
        ${PROJ_LIBRARIES}
        yaml-cpp
        )

