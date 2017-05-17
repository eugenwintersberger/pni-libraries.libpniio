
#in this case we assume that the user has a particular source or 
#global installation in mind - this selection is independent of the 
#platform and compiler we are on 
if(pnicore_DIR)
    message(STATUS "Looking for a user defined pnicore cmake package")
    #we are definitely looking for a config file package here
    find_package(pnicore CONFIG REQUIRED)

    set(pnicore_LIBRARIES pnicore_shared)
    get_target_property(pnicore_INCLUDE_DIRS pnicore_shared INTERFACE_INCLUDE_DIRECTORIES)

else()
    #here should go the pkg-config configuration
    if(PKG_CONFIG_FOUND)
        message(STATUS "User pkg-config to search for pnicore")
    else()
        message(FATAL_ERROR "Could not find pkg-config - currently required to configure pnicore!")
    endif()
endif()

message(STATUS "Found pnicore headers in: ${pnicore_INCLUDE_DIRS}")
message(STATUS "pnicore libraries: ${pnicore_LIBRARIES}")



