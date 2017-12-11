set(XMLFILES  node_from_bad_file.xml
              node_from_str.xml
              inquery.xml
    )


foreach(XMLFILE ${XMLFILES})
    configure_file(${XMLFILE} ${XMLFILE} COPYONLY)
endforeach()
