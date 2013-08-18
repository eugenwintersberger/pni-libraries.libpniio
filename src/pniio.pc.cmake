prefix = @CMAKE_INSTALL_PREFIX@ 
exec_prefix = ${prefix}
includedir = ${prefix}/include
libdir = ${prefix}/lib

Name: @CMAKE_PROJECT_NAME@
Description: PNI IO library
Version: @LIBRARY_VERSION@
Cflags: -I${includedir} 
Requires: pnicore
Libs: -L${libdir} -lpniio -lhdf5 -lz -lboost_filesystem
