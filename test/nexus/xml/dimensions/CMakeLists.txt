

set(XMLFILES dim1.xml
             dim2.xml
             dim3.xml
             dim4.xml
             dim5.xml
             dim6.xml)


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()

