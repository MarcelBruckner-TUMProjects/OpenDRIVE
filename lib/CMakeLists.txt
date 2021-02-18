########################################################################################################################
### PUGI XML ###
########################################################################################################################

# Download and unpack pugixml at configure time
configure_file(CMakeLists.txt.in pugixml-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pugixml-download)
if (result)
    message(FATAL_ERROR "CMake step for pugixml failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pugixml-download)
if (result)
    message(FATAL_ERROR "Build step for pugixml failed: ${result}")
endif ()

# Add pugixml directly to our build.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/pugixml-src
        ${CMAKE_CURRENT_BINARY_DIR}/pugixml-build
        EXCLUDE_FROM_ALL)

########################################################################################################################
### Library ###
########################################################################################################################

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PROJ)

add_library(libOpenDRIVE
        HDMap.cpp
        Geometry.cpp
        Elevation.cpp
        GeoReference.cpp
        Header.cpp
        ParamPoly3.cpp
        Road.cpp
        Shape.cpp
        TrafficRule.cpp
        Type.cpp
        )

target_include_directories(libOpenDRIVE
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVE
        ${Boost_LIBRARIES}
        ${PROJ_LIBRARIES}
        pugixml
        )
