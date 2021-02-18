########################################################################################################################
### Library ###
########################################################################################################################

execute_process (
    COMMAND bash -c "xsdcxx cxx-tree standard/xsd_schema/*.xsd"
)

add_subdirectory(standard)

add_library(libOpenDRIVE
        Core.cpp
        Junction.cpp
        Lane.cpp
        Object.cpp
        Railroad.cpp
        Road.cpp
        Signal.cpp
        )

target_include_directories(libOpenDRIVE
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(libOpenDRIVE libOpenDRIVEStandard)
