set(IMAGE_FILES data_readers.svg
                image_reader_usage.svg
                spreadsheet_reader_usage.svg)
            
foreach(IMAGE ${IMAGE_FILES})
    configure_file(${IMAGE} ${IMAGE} COPYONLY)
endforeach()