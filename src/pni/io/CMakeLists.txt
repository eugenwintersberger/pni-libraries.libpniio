set(HEADER_FILES column_info.hpp
                 data_reader.hpp
                 deprecation_warning.hpp
                 image_channel_info.hpp
                 image_info.hpp
                 image_reader.hpp
                 spreadsheet_reader.hpp
                 strutils.hpp
                 exceptions.hpp
                 parsers.hpp
                 formatters.hpp
                 container_io_config.hpp
                 windows.hpp
                 )

set(SOURCES_FILES column_info.cpp
                  data_reader.cpp
                  image_info.cpp
                  image_reader.cpp
                  spreadsheet_reader.cpp
                  exceptions.cpp
                  container_io_config.cpp
                  strutils.cpp)
                 
set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES})
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES})
                 
install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io)


add_subdirectory("cbf")
add_subdirectory("fio")
add_subdirectory("nx")
add_subdirectory("parsers")
add_subdirectory("formatters")
add_subdirectory("tiff")

add_library(pniio SHARED ${PNIIO_SOURCE_FILES} ${PNIIO_HEADER_FILES})

target_include_directories(pniio
PRIVATE ${PROJECT_SOURCE_DIR}/src
INTERFACE
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#add_dependencies(pniio config.hpp)
set_target_properties(pniio PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

target_link_libraries(pniio
                      PUBLIC pnicore_shared h5cpp_shared
                      ${HDF5_LIBRARIES}
                      Boost::filesystem
                      Boost::regex
                      Boost::date_time
                      )
target_compile_definitions(pniio PUBLIC BOOST_ALL_DYN_LINK)

#install code
install(TARGETS pniio
        EXPORT pniio_targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT libraries
        )

install(EXPORT pniio_targets
DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
COMPONENT development)
