prefix = @CMAKE_INSTALL_PREFIX@ 
exec_prefix = ${prefix}
includedir = ${prefix}/include
libdir = ${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: @CMAKE_PROJECT_NAME@
Description: PNI IO library
Version: @LIBRARY_VERSION@
Cflags: -I${includedir} -I@HDF5_INCLUDE_DIRS@
Requires: pnicore
Libs: -L${libdir} -L@HDF5_LIBRARY_DIRS@ -lpniio -lhdf5 -lz -lboost_filesystem
