set(SZLIB_LIBRARIES)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    #first we have to find the c-library
    if(SZLIB_LIBRARYDIR)
        #user provided HDF5_C_LIBRARY_DIRS
        message(STATUS "Try to find SZLIB library in: ${SZLIB_LIBRARYDIR}")
        find_library(SZLIB_LIBRARIES libszip "${SZLIB_LIBRARYDIR}")
    else()
        #without use provided HDF5_C_LIBARY_DIRS
        find_library(SZLIB_LIBRARIES libszip)
    endif()
   
    message(STATUS "Found: ${SZLIB_LIBRARIES}")
    if(SZLIB_LIBRARIES-NOTFOUND)
        message(FATAL "SZLIB runtime binaries not found!")
    else()
        message(STATUS "Found ZLIB: ${SZLIB_LIBRARIES}")
    endif()


    #now we have to look for the header file
    if(SZLIB_INCLUDEDIR)
        message(STATUS "Try to find SZLIB headers in: ${SZLIB_INCLUDEDIR}")
        find_file(SZLIB_HEADERS "szlib.h" ${SZLIB_INCLUDEDIR})
    else()
        find_file(SZLIB_HEADERS "szlib.h")
    endif()

    if(SZLIB_HEADERS-NOTFOUND)
        message(FATAL "SZLIB header files not found!")
    else()
        get_filename_component(SZLIB_INCLUDE_DIRS ${SZLIB_HEADERS} PATH)
        message(STATUS "Found SZLIB headers in: ${SZLIB_INCLUDE_DIRS}")
        include_directories(${SZLIB_INCLUDE_DIRS})
    endif()

endif()

