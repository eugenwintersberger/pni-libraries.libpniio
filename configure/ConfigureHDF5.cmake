


message(STATUS "Try to configure HDF5 manually via tools ...")
find_package(HDF5 REQUIRED C)


link_directories(${HDF5_LIBRARY_DIRS})
add_definitions(-DH5_BUILT_AS_DYNAMIC_LIB)


# add HDF5 include directories - we need them everywhere in the code
include_directories(${HDF5_INCLUDE_DIRS})
