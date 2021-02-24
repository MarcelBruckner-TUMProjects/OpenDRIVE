########################################################################################################################
### Library ###
########################################################################################################################

add_subdirectory(standard)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PROJ)

add_library(libOpenDRIVE
        HDMap.cpp
        Road.cpp
        Object.cpp
        OpenDriveWrapper.cpp
        Geometry.cpp
        Vector.cpp
        )

target_include_directories(libOpenDRIVE
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVE
        ${Boost_LIBRARIES}
        ${PROJ_LIBRARIES}
        libOpenDRIVEStandard
        )
