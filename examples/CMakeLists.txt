cmake_minimum_required(VERSION 3.10)


########################################################################################################################
### Includes ###
########################################################################################################################

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)

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

add_executable(basicOpendrive16Loading basicOpendrive16Loading.cpp)
target_link_libraries(basicOpendrive16Loading PUBLIC OpenDRIVE-lib Boost::program_options)
target_include_directories(basicOpendrive16Loading PUBLIC "${PROJECT_BINARY_DIR}")

include_directories(../misc/)
