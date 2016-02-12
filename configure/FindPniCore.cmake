
if(NOT PKG_CONFIG_FOUND)
    message(STATUS "Could not find pkg-config ... try without it!")
    
    if(PNICORE_LIBRARYDIR)
        message(STATUS "Looking for pnicore in: ${PNICORE_LIBRARYDIR}")
        find_library(PNICORE_PKG_LIBRARIES pnicore "${PNICORE_LIBRARYDIR}")
    else()
        find_library(PNICORE_PKG_LIBRARIES pnicore)
    endif()
    
    if(PNICORE_PKG_LIBRARIES-NOTFOUND)
        message(FATAL "Could not find pnicore libraries")
    else()
        message(STATUS "Found: ${PNICORE_PKG_LIBRARIES}")
    endif()

    if(PNICORE_INCLUDEDIR)
        message(STATUS "Looking for pnicore headers in: ${PNICORE_INCLUDEDIR}")
        find_file(PNICORE_HEADERS "types.hpp" "${PNICORE_INCLUDEDIR}/pni/core")
    else()
        find_file(PNICORE_HEADERS "types.hpp")
    endif()

    if(PNICORE_HEADERS-NOTFOUND)
        message(FATAL "Could not find pnicore header files")
    else()
        message(STATUS "Found: ${PNICORE_HEADERS}")
    endif()

    include_directories(${PNICORE_INCLUDEDIR})

else()
    #the only thing we have to do here is to check for pnicore
    pkg_search_module(PNICORE_PKG REQUIRED pnicore)
endif()
