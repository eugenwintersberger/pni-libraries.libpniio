# if the required Boost targets do not exist we have to add them
if((NOT TARGET pnicore_shared))

    find_package(pnicore REQUIRED)
    #
    # this will also pull in Boost::system and Boost::program_options
    #
endif()

if((NOT TARGET Boost::filesystem) OR (NOT TARGET Boost::regex) or (NOT TARGET Boost::date_time))

	find_package(Boost 1.41 REQUIRED COMPONENTS filesystem regex date_time)
	if(NOT Boost_FOUND)
		message(FATAL_ERROR "Could not find boost libraries - you may have to set the BOOST_ROOT variable!")
	endif()
endif()

link_directories(${Boost_LIBRARY_DIRS})
include(${CMAKE_CURRENT_LIST_DIR}/pniio_targets.cmake)
