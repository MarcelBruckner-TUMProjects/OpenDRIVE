cmake_minimum_required(VERSION 3.17)

find_package(XercesC REQUIRED)

if (NOT OPENDRIVE_1_6)
    message("Using OpenDrive Standard 1.4")
    add_library(OpenDRIVEStandard
            standard_1_4/OpenDRIVE_1.4H_Schema_Files.cxx
            )

    configure_file(standard_1_4/OpenDRIVE_1.4H_Schema_Files.xsd COPYONLY)

    target_include_directories(OpenDRIVEStandard
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
            )
else ()
    message("Using OpenDrive Standard 1.6")
    add_library(OpenDRIVEStandard
            standard_1_6/opendrive_16_core.cxx
            standard_1_6/opendrive_16_road.cxx
            standard_1_6/opendrive_16_railroad.cxx
            standard_1_6/opendrive_16_junction.cxx
            standard_1_6/opendrive_16_lane.cxx
            standard_1_6/opendrive_16_object.cxx
            )

    configure_file(standard_1_6/opendrive_16_core.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_road.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_railroad.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_junction.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_lane.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_object.xsd COPYONLY)
    configure_file(standard_1_6/opendrive_16_signal.xsd COPYONLY)


    target_include_directories(OpenDRIVEStandard
            PUBLIC ${XSD_INCLUDE_DIR}
            )
endif ()

target_link_libraries(OpenDRIVEStandard XercesC::XercesC)

if (WITH_TESTS)
    add_subdirectory(googletest)
endif ()
add_subdirectory(yaml-cpp)
