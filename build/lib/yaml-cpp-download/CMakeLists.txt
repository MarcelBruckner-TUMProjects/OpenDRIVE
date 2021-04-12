cmake_minimum_required(VERSION 2.8.12)

project(yaml-cpp-download NONE)

include(ExternalProject)
ExternalProject_Add(yaml-cpp
  GIT_REPOSITORY    https://github.com/jbeder/yaml-cpp.git
  GIT_TAG           master
  SOURCE_DIR        "/home/brucknem/Repositories/OpenDRIVE/build/lib/yaml-cpp-src"
  BINARY_DIR        "/home/brucknem/Repositories/OpenDRIVE/build/lib/yaml-cpp-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
