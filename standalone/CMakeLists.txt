cmake_minimum_required(VERSION 3.10)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

########################################################################################################################
### STANDALONE ###
########################################################################################################################
add_executable(Converter Converter.cpp)
target_link_libraries(Converter PUBLIC libOpenDRIVE Boost::program_options)
target_include_directories(Converter PUBLIC "${PROJECT_BINARY_DIR}")

