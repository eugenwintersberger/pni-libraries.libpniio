prefix = @CMAKE_INSTALL_PREFIX@ 
exec_prefix = ${prefix}
includedir = ${prefix}/include
libdir = ${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: @CMAKE_PROJECT_NAME@
Description: PNI NeXus library
Version: @LIBRARY_VERSION@
Cflags: -I${includedir} -I@HDF5_INCLUDE_DIRS@
Requires: h5cpp
Libs: -L${libdir} -lpninexus
Libs.private:  -L@HDF5_LIBRARY_DIRS@ -lhdf5 -lhdf5_hl -lz -lboost_filesystem
