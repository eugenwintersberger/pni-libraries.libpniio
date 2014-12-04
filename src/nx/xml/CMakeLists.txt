set(SOURCES 
            attribute_data.cpp 
            node_data.cpp 
            node.cpp
            decoder.cpp
            #io_object.cpp
            dimensions.cpp
            #field.cpp
            )

add_library(xml_objects OBJECT ${SOURCES})
