cmake_minimum_required(VERSION 3.10)

########################################################################################################################
### Includes ###
########################################################################################################################

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
### STANDALONE ###
########################################################################################################################
add_executable(Converter Converter.cpp)
target_link_libraries(Converter PUBLIC OpenDRIVE-lib Boost::program_options)
target_include_directories(Converter PUBLIC "${PROJECT_BINARY_DIR}")

