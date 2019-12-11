set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/column_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/data_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/deprecation_warning.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_channel_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/spreadsheet_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/strutils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/parsers.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/formatters.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_io_config.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/windows.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nexus.hpp
                 )

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/column_info.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/data_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_info.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/spreadsheet_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_io_config.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/strutils.cpp)
                 
# ============================================================================
# setting up the global lists for source and header files
# ============================================================================                
set(PNIIO_HEADER_FILES )
set(PNIIO_SOURCE_FILES )
                 
# ============================================================================
# install header files
# ============================================================================                
install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/io)


add_subdirectory("cbf")
add_subdirectory("fio")
add_subdirectory("parsers")
add_subdirectory("formatters")
add_subdirectory("tiff")
add_subdirectory("nexus")

# ============================================================================
# assemble list of header and source files used in the build 
# ============================================================================

set(PNIIO_HEADER_FILES ${PNIIO_HEADER_FILES} ${HEADER_FILES})
set(PNIIO_SOURCE_FILES ${PNIIO_SOURCE_FILES} ${SOURCE_FILES})

# ============================================================================
# adding header files to the doxygen build dependencies
# ============================================================================
add_doxygen_source_deps(${PNIIO_HEADER_FILES})

# ============================================================================
# building the library
# ============================================================================ 
foreach(SRC ${PNIIO_SOURCE_FILES})
    message(INFO ${SRC})
endforeach()

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
                      PUBLIC pnicore_shared h5cpp
                      ${HDF5_LIBRARIES}
                      Boost::filesystem
                      Boost::regex
                      Boost::date_time
                      )
target_compile_definitions(pniio PUBLIC BOOST_ALL_DYN_LINK)
target_compile_definitions(pniio PRIVATE DLL_BUILD) 

# ============================================================================
# install the library binaries and targets 
# ============================================================================
configure_file(pniio.pc.cmake pniio.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pniio.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
#
# export the targets which are latter used by the CMAKE package
# 
install(TARGETS pniio
        EXPORT pniio_targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT libraries
        )

#
# install the binaries
#
install(EXPORT pniio_targets
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)
