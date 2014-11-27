set(SOURCES attribute_data.cpp 
            node_data.cpp 
            xml_node.cpp
            dimensions.cpp
            field.cpp
            )

add_library(xml_objects OBJECT ${SOURCES})
