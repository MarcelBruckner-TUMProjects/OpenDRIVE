cmake_minimum_required(VERSION 3.10)

########################################################################################################################
### EXAMPLES ###
########################################################################################################################
add_executable(PrintGoogleLinks PrintGoogleLinks.cpp)
target_link_libraries(PrintGoogleLinks PUBLIC libOpenDRIVE)
target_include_directories(PrintGoogleLinks PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(CreateCSV CreateCSV.cpp)
target_link_libraries(CreateCSV PUBLIC libOpenDRIVE)
target_include_directories(CreateCSV PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(PrintCameraGoogleLink PrintCameraGoogleLink.cpp)
target_link_libraries(PrintCameraGoogleLink PUBLIC libOpenDRIVE)
target_include_directories(PrintCameraGoogleLink PUBLIC "${PROJECT_BINARY_DIR}")

include_directories(../misc/)
