########################################################################################################################
### Library ###
########################################################################################################################

execute_process (
    COMMAND bash -c "xsdcxx cxx-tree standard/xsd_schema/*.xsd'"
)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

add_library(libOpenDRIVEStandard ${SRC_FILES})

target_include_directories(libOpenDRIVEStandard
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVEStandard)
