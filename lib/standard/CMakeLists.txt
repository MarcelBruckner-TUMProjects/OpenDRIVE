cmake_minimum_required(VERSION 3.17)

find_package(XercesC REQUIRED)

add_library(libOpenDRIVEStandard
        OpenDRIVE_1.4H_Schema_Files.cxx
        )

configure_file(OpenDRIVE_1.4H_Schema_Files.xsd ./ COPYONLY)

target_include_directories(libOpenDRIVEStandard
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )
target_link_libraries(libOpenDRIVEStandard XercesC::XercesC)
