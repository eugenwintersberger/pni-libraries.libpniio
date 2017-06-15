# if the required Boost targets do not exist we have to add them
if((NOT TARGET pnicore_shared))

    find_package(pnicore REQUIRED)
    #
    # this will also pull in Boost::system and Boost::program_options
    #
endif()

set(BOOST_COMPONENTS)

if(NOT TARGET Boost::filesystem)
    list(APPEND BOOST_COMPONENTS filesystem)
endif()

if(NOT TARGET Boost::regex)
    list(APPEND BOOST_COMPONENTS regex)
endif()

if(NOT TARGET Boost::date_time)
    list(APPEND BOOST_COMPONENTS date_time)
endif()

message(STATUS "Required Boost components: ${BOOST_COMPONENTS}")
find_package(Boost 1.41 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Could not find boost libraries - you may have to set the BOOST_ROOT variable!")
endif()

link_directories(${Boost_LIBRARY_DIRS})
include(${CMAKE_CURRENT_LIST_DIR}/pniio_targets.cmake)
