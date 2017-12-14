set(XMLFILES input.xml)

foreach(F ${XMLFILES})
	configure_file(${F} ${F} COPYONLY)
endforeach()
		


