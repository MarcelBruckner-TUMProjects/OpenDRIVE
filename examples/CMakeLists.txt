cmake_minimum_required(VERSION 3.10)

########################################################################################################################
### TESTING ###
########################################################################################################################
add_executable(PrintGoogleLinks PrintGoogleLinks.cpp)
target_link_libraries(PrintGoogleLinks PUBLIC libOpenDRIVE)
target_include_directories(PrintGoogleLinks PUBLIC "${PROJECT_BINARY_DIR}")

include_directories(../misc/)
