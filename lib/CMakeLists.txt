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
        )

target_include_directories(libOpenDRIVE
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVE
        libOpenDRIVEStandard
        ${PROJ_LIBRARIES}
        )

