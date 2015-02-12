set(SOURCES 
            attribute_data.cpp 
            node_data.cpp 
            node.cpp
            io_object.cpp
            dimensions.cpp
            array_utils.cpp
            #field.cpp
            )

add_library(xml_objects OBJECT ${SOURCES})
