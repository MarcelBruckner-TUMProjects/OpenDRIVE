cmake_minimum_required(VERSION 3.10)


########################################################################################################################
### Includes ###
########################################################################################################################

include_directories(${PROJECT_SOURCE_DIR}/extern)
include_directories(${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
### EXAMPLES ###
########################################################################################################################
add_executable(PrintGoogleLinks PrintGoogleLinks.cpp)
target_link_libraries(PrintGoogleLinks PUBLIC OpenDRIVE-lib)
target_include_directories(PrintGoogleLinks PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(CreateCSV CreateYAML.cpp)
target_link_libraries(CreateCSV PUBLIC OpenDRIVE-lib)
target_include_directories(CreateCSV PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(PrintCameraGoogleLink PrintCameraGoogleLink.cpp)
target_link_libraries(PrintCameraGoogleLink PUBLIC OpenDRIVE-lib)
target_include_directories(PrintCameraGoogleLink PUBLIC "${PROJECT_BINARY_DIR}")

include_directories(../misc/)
