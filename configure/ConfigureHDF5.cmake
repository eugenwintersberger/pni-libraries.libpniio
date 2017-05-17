
if(hdf5_DIR)
    #look for a cmake package specified by the user or provided via the global
    #package registry

    find_package(hdf5 CONFIG REQUIRED)

    set(hdf5_LIBRARIES hdf5::hdf5-shared)
    get_target_property(hdf5_INCLUDE_DIRS hdf5::hdf5-shared INTERFACE_INCLUDE_DIRECTORIES)
else()
    message(FATAL_ERROR "HDF5 search without cmake not implemented yet")
endif()
add_definitions(-DH5_BUILT_AS_DYNAMIC_LIB)
message(STATUS "Found HDF5 headers in: ${hdf5_INCLUDE_DIRS}")
message(STATUS "Found HDF5 libraries: ${hdf5_LIBRARIES}")
get_target_property(FILE_NAME hdf5::hdf5-shared LOCATION)
get_filename_component(FILE_NAME ${FILE_NAME} DIRECTORY)
link_directories(${FILE_NAME})
message(STATUS "Found HDF5 library file: ${FILE_NAME}")
get_target_property(FILE_NAME hdf5::hdf5-shared INTERFACE_LINK_LIBRARIES)
message(STATUS "Found HDF5 link libraries: ${FILE_NAME}")

#if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
#    find_package(HDF5 NAMES hdf5 COMPONENTS C)
#    message(STATUS "HDF5 header files: ${HDF5_INCLUDE_DIRS}")
#    set(HDF5_FOUND TRUE)
#    #first we have to find the c-library
#    if(HDF5_C_LIBRARY_DIRS)
#        #user provided HDF5_C_LIBRARY_DIRS
#        message(STATUS "Try to find HDF5 library in: ${HDF5_C_LIBRARY_DIRS}")
#        find_library(HDF5_LIBRARIES libhdf5 "${HDF5_C_LIBRARY_DIRS}")
#    else()
#        #without use provided HDF5_C_LIBARY_DIRS
#        find_library(HDF5_LIBRARIES libhdf5)
#    endif()
#   
#    message(STATUS "Found: ${HDF5_LIBRARIES}")
#    if(HDF5_LIBRARIES-NOTFOUND)
#        set(HDF5_FOUND FALSE)
#    endif()
#
#    #generate the include path from the path of the library
#    get_filename_component(HDF5_C_LIBRARY_DIRS ${HDF5_LIBRARIES} PATH)
#    string(REGEX REPLACE "lib(64)*" "include" HDF5_INCLUDE_DIRS "${HDF5_C_LIBRARY_DIRS}")
#    message(STATUS "Found HDF5 library  in: ${HDF5_C_LIBRARY_DIRS}")
#    message(STATUS "Found HDF5 headers in: ${HDF5_INCLUDE_DIRS}")
#
#    #now we have to look for the header file
#    find_file(HDF5_HEADERS "hdf5.h" ${HDF5_INCLUDE_DIRS} "${HDF5_INCLUDE_DIRS}/hdf5")
#    if(HDF5_HEADERS-NOTFOUND)
#        set(HDF5_FOUND FALSE)
#    endif()
#
#    get_filename_component(HDF5_INCLUDE_DIRS ${HDF5_HEADERS} PATH)
#    include_directories(${HDF5_INCLUDE_DIRS}) 
#else()
#    include(FindHDF5)
#endif()
#
#message(STATUS "${HDF5_FOUND}")
#if(NOT HDF5_FOUND)
#    #could not find HDF5 - stop configuration step
#    message("HDF5 not found:")
#    message(FATAL "Please set HDF5_C_INCLUDE_DIRS and HDF5_LIBRARY_DIRS manually!")
#endif()
