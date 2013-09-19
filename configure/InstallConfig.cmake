#check the installation configuration 

#====================for Linux systems==================================
# for systems with cmake >= 2.8 the GNUInstallDirs module provides all the
# installation paths. More precise this module defines all the variables
# required for the installation of the code. These variables are
#
# CMAKE_INSTALL_LIBDIR - path for library binaries 
# CMAKE_INSTALL_SYSCONFDIR - configuration direcotry (typically etc)
# CMAKE_INSTALL_DOCDIR - installation path for the documentation
# CMAKE_INSTALL_INCLUDEDIR - installation path for the header files
# 
# This module is particularly useful for Debian systems as it automatically
# determines the installation path for the libraries on multiarch systems.
#
# This module is not available on cmake 2.6 and thus we have to define this 
# variables manually
# 
if(("${CMAKE_FAMILY_VERSION}" EQUAL "2.6") OR ("${CMAKE_VERSION}" EQUAL "2.8.4"))
    #most of the paths are canonic and thus easy to define
    set(CMAKE_INSTALL_SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc")
    set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc")
    set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")

    #the library installation path is more difficult as we have several options
    #here
    # RedHat systems 32Bit: lib
    # RedHat systems 64Bit: lib64
    # Debian 32/64Bit     : lib
    # Debian multiarch    : lib/<ARCHSIG>
    #
    #However, as the time of writing this, the only systems that are available
    #that do not run cmake 2.8 are old RHEL 6 and 5 systems. Thus we can set the 
    #default to lib64 in case of 64Bit systems and to lib in case of 32Bit
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib64")
    else()
        set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
    endif()
else()
    include(GNUInstallDirs)
endif()

