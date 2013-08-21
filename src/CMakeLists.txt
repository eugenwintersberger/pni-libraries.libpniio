
#gather all source files for the library
file(GLOB_RECURSE SOURCES *.c*)

link_directories(${PNICORE_PKG_LIBRARY_DIRS} ${HDF5_LIBRARY_DIRS})
include_directories(${PNICORE_PKG_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})

add_library(pniio SHARED ${SOURCES})
add_dependencies(pniio config.hpp)
set_target_properties(pniio PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")
target_link_libraries(pniio hdf5 z boost_date_time boost_filesystem ${PNICORE_PKG_LIBRARIES})

#install code
install(TARGETS pniio LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

#have to create the pkg-config file
CONFIGURE_FILE(pniio.pc.cmake pniio.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pniio.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")


