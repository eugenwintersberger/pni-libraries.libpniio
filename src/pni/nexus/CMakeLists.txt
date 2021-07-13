set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/file.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/date_time.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/base_class_factory.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/predicates.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/containers.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_factory.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/hdf5_support.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/path.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/field_factory.hpp
	)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/file.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/date_time.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/base_class_factory.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/predicates.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/containers.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/object_builder.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/datatype_factory.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/hdf5_support.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/field_factory.cpp
	)

add_subdirectory(xml)	
add_subdirectory(path)
install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/nexus)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)