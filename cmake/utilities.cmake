#
# some utility functions which make life easier
#

function(PNINEXUS_MESSAGE LEVEL)
	message(${LEVEL} "PNINEXUS: ${ARGN}")
endfunction()

function(copy_to_current_build)
	foreach(f ${ARGV})
		configure_file(${f} ${f} COPYONLY)
	endforeach()

endfunction()
