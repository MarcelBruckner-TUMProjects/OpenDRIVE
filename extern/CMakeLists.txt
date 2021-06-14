cmake_minimum_required(VERSION 3.17)

find_package(XercesC REQUIRED)

add_library(OpenDRIVEStandard
        standard_1_4/OpenDRIVE_1.4H_Schema_Files.cxx
        )

configure_file(standard_1_4/OpenDRIVE_1.4H_Schema_Files.xsd COPYONLY)

target_include_directories(OpenDRIVEStandard
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )
target_link_libraries(OpenDRIVEStandard XercesC::XercesC)

if (WITH_TESTS)
    add_subdirectory(googletest)
endif ()
add_subdirectory(yaml-cpp)
