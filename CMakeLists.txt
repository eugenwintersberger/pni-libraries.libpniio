cmake_minimum_required(VERSION 2.6)
include(GNUInstallDirs)
project(PNIIO)

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

#need to define the version of the library
set(MAJOR_VERSION "0")
set(MINOR_VERSION "9")
set(PATCH_VERSION "4")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION "1")

include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")

