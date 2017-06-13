#gather all source files for the library
set(SOURCES column_info.cpp
             data_reader.cpp
             image_info.cpp
             image_reader.cpp
             spreadsheet_reader.cpp
             exceptions.cpp
             container_io_config.cpp
             strutils.cpp)
include_directories(${pnicore_INCLUDE_DIRS} ${hdf5_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
add_definitions(-DDLL_BUILD)
#first we need to build the C-filter code
add_subdirectory(cbf)
add_subdirectory(fio)
add_subdirectory(nx)
add_subdirectory(tiff)
add_subdirectory(formatters)
add_subdirectory(parsers)


add_library(pniio SHARED ${SOURCES}
                         $<TARGET_OBJECTS:cbf_objects>
                         $<TARGET_OBJECTS:fio_objects>
                         $<TARGET_OBJECTS:nx_objects>
                         $<TARGET_OBJECTS:h5_objects>
                         $<TARGET_OBJECTS:xml_objects>
                         $<TARGET_OBJECTS:tiff_objects>
                         $<TARGET_OBJECTS:nx_path>
                         $<TARGET_OBJECTS:algorithms>
                         $<TARGET_OBJECTS:formatter_objects>
                         $<TARGET_OBJECTS:parser_objects>
)
#add_dependencies(pniio config.hpp)
set_target_properties(pniio PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

target_link_libraries(pniio
                      PUBLIC pnicore_shared
                      ${hdf5_LIBRARIES}
                      ${HDF5_LIBRARIES}
                      Boost::filesystem
                      Boost::regex
                      Boost::date_time
                      )
target_compile_definitions(pniio PUBLIC BOOST_ALL_DYN_LINK)

#install code
install(TARGETS pniio
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )

#have to create the pkg-config file
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    CONFIGURE_FILE(pniio.pc.cmake ./src/pniio.pc @ONLY)
else()
    CONFIGURE_FILE(pniio.pc.cmake pniio.pc @ONLY)
endif()

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pniio.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
