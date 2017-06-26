

if(CONAN_HDF5)

    conan_cmake_run(REQUIRES "hdf5/1.10.1@wintersb/stable"
                    BASIC_SETUP
                    IMPORTS "bin, *.dll -> bin"
                    BUILD missing)

    #using here the native HDF5 package is most probably the best solution
    message(STATUS "HDF5 conan found: ${CONAN_HDF5_ROOT}")
    if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
        #package files installation directory on Windows
        set(hdf5_DIR ${CONAN_HDF5_ROOT}/cmake)
    else()
        #package file installation directory on Unix systems
        set(hdf5_DIR ${CONAN_HDF5_ROOT}/share/cmake)
    endif()

endif()


message(STATUS "Try to configure HDF5 manually via tools ...")
find_package(HDF5 REQUIRED C)

#we usually get a list of libraries we have to link
foreach(LIB ${HDF5_LIBRARIES})

    string(REGEX MATCH "hdf5" MATCH_RESULT "${LIB}")

    if(MATCH_RESULT)
        get_filename_component(HDF5_LIBRARY_DIRS ${LIB} DIRECTORY)
    endif()

endforeach()

message(STATUS "HDF5 header files: ${HDF5_INCLUDE_DIRS}")
message(STATUS "HDF5 libraries: ${HDF5_LIBRARIES}")
message(STATUS "HDF5 library directory: ${HDF5_LIBRARY_DIRS}")
link_directories(${HDF5_LIBRARY_DIRS})
add_definitions(-DH5_BUILT_AS_DYNAMIC_LIB)


# add HDF5 include directories - we need them everywhere in the code
include_directories(${HDF5_INCLUDE_DIRS})
