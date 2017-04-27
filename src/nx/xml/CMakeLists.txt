set(SOURCES data_node.cpp 
            node.cpp
            io_node.cpp
            dimensions.cpp
            array_utils.cpp
            field.cpp
            link.cpp
            )

add_library(xml_objects OBJECT ${SOURCES})
set_property(TARGET xml_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
