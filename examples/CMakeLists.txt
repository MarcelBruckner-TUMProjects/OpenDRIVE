cmake_minimum_required(VERSION 3.10)

if (OPENDRIVE_1_4)
    ########################################################################################################################
    ### Includes ###
    ########################################################################################################################

    include_directories(${PROJECT_SOURCE_DIR}/extern)
    include_directories(${PROJECT_SOURCE_DIR}/include)
    include_directories(../misc/)

    find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

    ########################################################################################################################
    ### EXAMPLES ###
    ########################################################################################################################
    add_executable(PrintGoogleLinks PrintGoogleLinks.cpp)
    target_link_libraries(PrintGoogleLinks PUBLIC OpenDRIVE-lib Boost::program_options)
    target_include_directories(PrintGoogleLinks PUBLIC "${PROJECT_BINARY_DIR}")

    add_executable(CreateCSV CreateYAML.cpp)
    target_link_libraries(CreateCSV PUBLIC OpenDRIVE-lib Boost::program_options)
    target_include_directories(CreateCSV PUBLIC "${PROJECT_BINARY_DIR}")

    add_executable(PrintCameraGoogleLink PrintCameraGoogleLink.cpp)
    target_link_libraries(PrintCameraGoogleLink PUBLIC OpenDRIVE-lib Boost::program_options)
    target_include_directories(PrintCameraGoogleLink PUBLIC "${PROJECT_BINARY_DIR}")

    add_executable(SampleLanes SampleLanes.cpp)
    target_link_libraries(SampleLanes PUBLIC OpenDRIVE-lib Boost::program_options)
    target_include_directories(SampleLanes PUBLIC "${PROJECT_BINARY_DIR}")
else ()
    message("The examples can only be built if the OpenDRIVE 1.4 standard is present in ./extern/")
endif ()
