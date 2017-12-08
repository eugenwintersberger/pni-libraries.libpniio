set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/file.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/date_time.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/base_class.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/predicates.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/transformations.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/containers.hpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.hpp
	)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/file.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/date_time.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/base_class.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/predicates.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.cpp
	             ${CMAKE_CURRENT_SOURCE_DIR}/containers.cpp
	)

	
install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io/nexus)
       
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES} PARENT_SCOPE)
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)