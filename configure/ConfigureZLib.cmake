set(ZLIB_LIBRARIES)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(ZLIB_FOUND TRUE)
    #first we have to find the c-library
    if(ZLIB_LIBRARYDIR)
        #user provided HDF5_C_LIBRARY_DIRS
        message(STATUS "Try to find ZLIB library in: ${ZLIB_LIBRARYDIR}")
        find_library(ZLIB_LIBRARIES libzlib "${ZLIB_LIBRARYDIR}")
    else()
        #without use provided HDF5_C_LIBARY_DIRS
        find_library(ZLIB_LIBRARIES libzlib)
    endif()
   
    message(STATUS "Found: ${ZLIB_LIBRARIES}")
    if(ZLIB_LIBRARIES-NOTFOUND)
        message(FATAL "ZLIB runtime binaries not found!")
    else()
        message(STATUS "Found ZLIB: ${ZLIB_LIBRARIES}")
    endif()


    #now we have to look for the header file
    if(ZLIB_INCLUDEDIR)
        message(STATUS "Try to find ZLIB headers in: ${ZLIB_INCLUDEDIR}")
        find_file(ZLIB_HEADERS "zlib.h" ${ZLIB_INCLUDEDIR})
    else()
        find_file(ZLIB_HEADERS "zlib.h")
    endif()

    if(ZLIB_HEADERS-NOTFOUND)
        message(FATAL "ZLIB header files not found!")
    else()
        get_filename_component(ZLIB_INCLUDE_DIRS ${ZLIB_HEADERS} PATH)
        message(STATUS "Found ZLIB headers in: ${ZLIB_INCLUDE_DIRS}")
        include_directories(${ZLIB_INCLUDE_DIRS})
    endif()

endif()

