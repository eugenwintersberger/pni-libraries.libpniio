if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(HDF5_FOUND TRUE)
    #first we have to find the c-library
    if(HDF5_C_LIBRARY_DIRS)
        #user provided HDF5_C_LIBRARY_DIRS
        message(STATUS "Try to find HDF5 library in: ${HDF5_C_LIBRARY_DIRS}")
        find_library(HDF5_LIBRARIES libhdf5 "${HDF5_C_LIBRARY_DIRS}")
    else()
        #without use provided HDF5_C_LIBARY_DIRS
        find_library(HDF5_LIBRARIES libhdf5)
    endif()
   
    message(STATUS "Found: ${HDF5_LIBRARIES}")
    if(HDF5_LIBRARIES-NOTFOUND)
        set(HDF5_FOUND FALSE)
    endif()

    #generate the include path from the path of the library
    get_filename_component(HDF5_C_LIBRARY_DIRS ${HDF5_LIBRARIES} PATH)
    string(REGEX REPLACE "lib(64)*" "include" HDF5_INCLUDE_DIRS "${HDF5_C_LIBRARY_DIRS}")
    message(STATUS "Found HDF5 library  in: ${HDF5_C_LIBRARY_DIRS}")
    message(STATUS "Found HDF5 headers in: ${HDF5_INCLUDE_DIRS}")

    #now we have to look for the header file
    find_file(HDF5_HEADERS "hdf5.h" ${HDF5_INCLUDE_DIRS} "${HDF5_INCLUDE_DIRS}/hdf5")
    if(HDF5_HEADERS-NOTFOUND)
        set(HDF5_FOUND FALSE)
    endif()

    get_filename_component(HDF5_INCLUDE_DIRS ${HDF5_HEADERS} PATH)
    include_directories(${HDF5_INCLUDE_DIRS}) 
else()
    include(FindHDF5)
endif()

message(STATUS "${HDF5_FOUND}")
if(NOT HDF5_FOUND)
    #could not find HDF5 - stop configuration step
    message("HDF5 not found:")
    message(FATAL "Please set HDF5_C_INCLUDE_DIRS and HDF5_LIBRARY_DIRS manually!")
endif()
