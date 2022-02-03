
find_package(h5cpp REQUIRED)
get_target_property(H5CPP_LIBRARIES h5cpp::h5cpp INTERFACE_LINK_LIBRARIES)
get_target_property(H5CPP_DEFINITIONS h5cpp::h5cpp INTERFACE_COMPILE_DEFINITIONS)
get_target_property(H5CPP_INCLUDE_DIRS h5cpp::h5cpp INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(H5CPP_LIBRARY_DIRS h5cpp::h5cpp INTERFACE_LINK_DIRECTORIES)
message(STATUS "==============================================================")
message(STATUS "========================Found h5cpp===========================")
message(STATUS "==============================================================")
message(STATUS "Found h5cpp libraries in: ${H5CPP_LIBRARY_DIRS}")
message(STATUS "Found h5cpp libraries: ${H5CPP_LIBRARIES}")
message(STATUS "Found h5cpp headers: ${H5CPP_INCLUDE_DIRS}")
message(STATUS "Found h5cpp definitions: ${H5CPP_DEFINITIONS}")
message(STATUS "Found h5cpp h5cpp_VERSION = ${h5cpp_VERSION}")
message(STATUS "==============================================================")


