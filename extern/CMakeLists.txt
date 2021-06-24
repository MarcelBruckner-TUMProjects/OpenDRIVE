cmake_minimum_required(VERSION 3.17)

find_package(XercesC REQUIRED)

if (OPENDRIVE_1_4)
    message("Using OpenDrive Standard 1.4")
    file(GLOB opendrive_1_4_cxx "opendrive_1_4/*.cxx")
    file(GLOB opendrive_1_4_xsd "opendrive_1_4/*.xsd")
endif ()
if (OPENDRIVE_1_6)
    message("Using OpenDrive Standard 1.6")
    file(GLOB opendrive_1_6_cxx "opendrive_1_6/*.cxx")
    file(GLOB opendrive_1_6_xsd "opendrive_1_6/*.xsd")
endif ()

if (OPENDRIVE_1_4 OR OPENDRIVE_1_6)
    add_library(OpenDRIVEStandard ${opendrive_1_4_cxx} ${opendrive_1_6_cxx})
    file(COPY ${opendrive_1_4_xsd} ${opendrive_1_6_xsd} DESTINATION .)
    target_include_directories(OpenDRIVEStandard
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
            )

    target_link_libraries(OpenDRIVEStandard XercesC::XercesC)

    if (WITH_TESTS)
        add_subdirectory(googletest)
    endif ()
    add_subdirectory(yaml-cpp)
    add_subdirectory(tinyxml2)
endif ()
